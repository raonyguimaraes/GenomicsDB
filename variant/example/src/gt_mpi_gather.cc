#include <iostream>
#include <string>
#include <getopt.h>
#include <mpi.h>
#include "libtiledb_variant.h"
#include "run_config.h"
#include "timer.h"
#include "broad_combined_gvcf.h"

#ifdef USE_BIGMPI
#include "bigmpi.h"
#endif

#ifdef USE_GPERFTOOLS
#include "gperftools/profiler.h"
#endif

enum ArgsEnum
{
  ARGS_IDX_SKIP_QUERY_ON_ROOT=1000,
  ARGS_IDX_PRODUCE_BROAD_GVCF
};

#define MegaByte (1024*1024)

#ifdef DO_PROFILING
enum TimerTypesEnum
{
  TIMER_TILEDB_QUERY_RANGE_IDX=0u,
  TIMER_BINARY_SERIALIZATION_IDX,
  TIMER_MPI_GATHER_IDX,
  TIMER_ROOT_BINARY_DESERIALIZATION_IDX,
  TIMER_JSON_PRINTING_IDX,
  TIMER_NUM_TIMERS
};

auto g_timer_names = std::vector<std::string>
{
  "TileDB-query",
  "Binary-serialization",
  "MPI-gather",
  "Binary-deserialization",
  "JSON-printing"
};
#endif

#ifdef NDEBUG
#define ASSERT(X) if(!(X)) { std::cerr << "Assertion failed - exiting\n"; exit(-1); }
#else
#define ASSERT(X) assert(X)
#endif

void run_range_query(const VariantQueryProcessor& qp, const VariantQueryConfig& query_config, const std::string& output_format,
    int num_mpi_processes, int my_world_mpi_rank, bool skip_query_on_root)
{
  GTProfileStats* stats_ptr = 0;
#ifdef DO_PROFILING
  //Performance measurements
  Timer timer;
  std::vector<double> timings(2u*TIMER_NUM_TIMERS, 0);  //[cpu-time,wall-clock time]
  ASSERT(g_timer_names.size() == TIMER_NUM_TIMERS);
  GTProfileStats stats;
  stats_ptr = &stats;
#endif
  //Variants vector
  std::vector<Variant> variants;
  //Perform query if not root or !skip_query_on_root
  if(my_world_mpi_rank != 0 || !skip_query_on_root)
  {
#ifdef DO_PROFILING
    timer.start();
#endif
    for(auto i=0u;i<query_config.get_num_column_intervals();++i)
      qp.gt_get_column_interval(qp.get_array_descriptor(), query_config, i, variants, 0, stats_ptr);
#ifdef DO_PROFILING
    timer.stop();
    timer.get_last_interval_times(timings, TIMER_TILEDB_QUERY_RANGE_IDX);
#endif
  }
#ifdef DO_PROFILING
  timer.start();
#endif
#if VERBOSE>0
  std::cerr << "[Rank "<< my_world_mpi_rank << " ]: Completed query, obtained "<<variants.size()<<" variants\n";
#endif
  //serialized variant data
  std::vector<uint8_t> serialized_buffer;
  serialized_buffer.resize(1000000u);       //1MB, arbitrary value - will be resized if necessary by serialization functions
  uint64_t serialized_length = 0ull;
  for(const auto& variant : variants)
    variant.binary_serialize(serialized_buffer, serialized_length);
#if VERBOSE>0
  std::cerr << "[Rank "<< my_world_mpi_rank << " ]: Completed serialization, serialized data size "
    << std::fixed << std::setprecision(3) << ((double)serialized_length)/MegaByte  << " MBs\n";
#endif
#ifdef DO_PROFILING
  timer.stop();
  timer.get_last_interval_times(timings, TIMER_BINARY_SERIALIZATION_IDX);
  //Gather profiling data at root
  auto num_timing_values_per_mpi_process = 2*(TIMER_BINARY_SERIALIZATION_IDX+1);
  std::vector<double> gathered_timings(num_mpi_processes*num_timing_values_per_mpi_process);
  ASSERT(MPI_Gather(&(timings[0]), num_timing_values_per_mpi_process, MPI_DOUBLE,
        &(gathered_timings[0]), num_timing_values_per_mpi_process, MPI_DOUBLE, 0, MPI_COMM_WORLD) == MPI_SUCCESS);
  timer.start();
#endif
  //Gather all serialized lengths (in bytes) at root
  std::vector<uint64_t> lengths_vector(num_mpi_processes, 0ull); 
  ASSERT(MPI_Gather(&serialized_length, 1, MPI_UINT64_T, &(lengths_vector[0]), 1, MPI_UINT64_T, 0, MPI_COMM_WORLD) == MPI_SUCCESS);
  //Total size of gathered data (valid at root only)
  auto total_serialized_size = 0ull;
  //Buffer to receive all gathered data, will be resized at root
  std::vector<uint8_t> receive_buffer(1u);
#ifdef USE_BIGMPI
  std::vector<MPI_Count> recvcounts(num_mpi_processes);
  std::vector<MPI_Aint> displs(num_mpi_processes);
#else
  //MPI uses int for counts and displacements
  std::vector<int> recvcounts(num_mpi_processes);
  std::vector<int> displs(num_mpi_processes);
#endif
  //root
  if(my_world_mpi_rank == 0)
  {
    for(auto val : lengths_vector)
      total_serialized_size += val;
#if VERBOSE>0
    std::cerr << "[Rank "<< my_world_mpi_rank << " ]: Gathered lengths, total size "
      << std::fixed << std::setprecision(3) << (((double)total_serialized_size)/MegaByte)<<" MBs\n";
#endif
#ifndef USE_BIGMPI
    if(total_serialized_size >= static_cast<uint64_t>(INT_MAX)) //max 32 bit signed int
    {
      std::cerr << "Serialized size beyond 32-bit int limit - exiting.\n";
      std::cerr <<  "Use the BigMPI library: https://github.com/jeffhammond/BigMPI and recompile the TileDB library with USE_BIGMPI=<path>\n";
      exit(-1);
    }
#endif
    receive_buffer.resize(total_serialized_size);
    auto curr_displ = 0ull;
    //Fill in recvcounts and displs vectors
    for(auto i=0u;i<recvcounts.size();++i)
    {
      auto curr_length = lengths_vector[i];
      recvcounts[i] = curr_length;
      displs[i] = curr_displ;
      curr_displ += curr_length;
    }
  }
  //Gather serialized variant data
#if VERBOSE>0
  if(my_world_mpi_rank == 0)
    std::cerr << "Starting MPIGather at root into buffer of size "<<((double)receive_buffer.size())/MegaByte<<"\n";
#endif
#ifdef USE_BIGMPI
  ASSERT(MPIX_Gatherv_x(&(serialized_buffer[0]), serialized_length, MPI_UINT8_T, &(receive_buffer[0]), &(recvcounts[0]), &(displs[0]), MPI_UINT8_T, 0, MPI_COMM_WORLD) == MPI_SUCCESS);
#else
  ASSERT(MPI_Gatherv(&(serialized_buffer[0]), serialized_length, MPI_UINT8_T, &(receive_buffer[0]), &(recvcounts[0]), &(displs[0]), MPI_UINT8_T, 0, MPI_COMM_WORLD) == MPI_SUCCESS);
#endif
#if VERBOSE>0
  if(my_world_mpi_rank == 0)
    std::cerr << "Completed MPI_Gather\n";
#endif
#ifdef DO_PROFILING
  timer.stop();
  timer.get_last_interval_times(timings, TIMER_MPI_GATHER_IDX);
  timer.start();
#endif
  //Deserialize at root
  if(my_world_mpi_rank == 0)
  {
    variants.clear();
    uint64_t offset = 0ull;
    while(offset < total_serialized_size)
    {
      variants.emplace_back();
      auto& variant = variants.back();
      qp.binary_deserialize(variant, query_config, receive_buffer, offset);
    }
#if VERBOSE>0
    std::cerr << "Completed binary deserialization at root\n";
#endif
#ifdef DO_PROFILING
    timer.stop();
    timer.get_last_interval_times(timings, TIMER_ROOT_BINARY_DESERIALIZATION_IDX);
    timer.start();
#endif
    print_variants(variants, output_format, query_config, std::cout);
#ifdef DO_PROFILING
    timer.stop();
    timer.get_last_interval_times(timings, TIMER_JSON_PRINTING_IDX);
    std::cerr << "Root received "<< std::fixed << std::setprecision(3) << (((double)total_serialized_size)/MegaByte)
      << " MBs of variant data in binary format\n";
    for(auto i=0u;i<TIMER_NUM_TIMERS;++i)
    {
      std::cerr << g_timer_names[i];
      if(i >= TIMER_MPI_GATHER_IDX) //only root info
        std::cerr << std::fixed << std::setprecision(3) << "," << timings[2*i] << ",," << timings[2*i+1u] << "\n";
      else
      {
        assert(2*i+1 < num_timing_values_per_mpi_process);
        for(auto j=0u;j<gathered_timings.size();j+=num_timing_values_per_mpi_process)
          std::cerr << std::fixed << std::setprecision(3) << "," << gathered_timings[j + 2*i];
        std::cerr << ",";
        for(auto j=0u;j<gathered_timings.size();j+=num_timing_values_per_mpi_process)
          std::cerr << std::fixed << std::setprecision(3) << "," << gathered_timings[j + 2*i + 1];
        std::cerr << "\n";
      }
    }
#endif
  }
}

#if defined(HTSDIR) && defined(BCFTOOLSDIR)
void scan_and_produce_Broad_GVCF(const VariantQueryProcessor& qp, const VariantQueryConfig& query_config, VCFAdapter& vcf_adapter,
    int num_mpi_processes, int my_world_mpi_rank, bool skip_query_on_root)
{
  BroadCombinedGVCFOperator gvcf_op(vcf_adapter, query_config);
  qp.scan_and_operate(qp.get_array_descriptor(), query_config, gvcf_op, 0, true);
}
#endif

int main(int argc, char *argv[]) {
  //Initialize MPI environment
  auto rc = MPI_Init(0, 0);
  if (rc != MPI_SUCCESS) {
    printf ("Error starting MPI program. Terminating.\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
  }
  //Get number of MPI processes
  int num_mpi_processes = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &num_mpi_processes);
  //Get my world rank
  int my_world_mpi_rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_world_mpi_rank);
#ifdef DEBUG
  //Print host, rank and LD_LIBRARY_PATH
  std::vector<char> hostname;
  hostname.resize(500u);
  gethostname(&(hostname[0]), hostname.size());
  if(my_world_mpi_rank == 0)
    std::cerr << "#processes "<<num_mpi_processes<<"\n";
  std::cerr << "Host : "<< &(hostname[0]) << " rank "<< my_world_mpi_rank << " LD_LIBRARY_PATH= "<<getenv("LD_LIBRARY_PATH") << "\n";
#endif
  // Define long options
  static struct option long_options[] = 
  {
    {"page-size",1,0,'p'},
    {"output-format",1,0,'O'},
    {"workspace",1,0,'w'},
    {"json-config",1,0,'j'},
    {"segment-size",1,0,'s'},
    {"skip-query-on-root",0,0,ARGS_IDX_SKIP_QUERY_ON_ROOT},
    {"produce-Broad-GVCF",0,0,ARGS_IDX_PRODUCE_BROAD_GVCF},
    {"array",1,0,'A'},
    {0,0,0,0},
  };
  int c;
  uint64_t page_size = 0u;
  std::string output_format = "";
  std::string workspace = "";
  std::string array_name = "";
  std::string json_config_file = "";
  bool skip_query_on_root = false;
  bool do_range_query = true;
  bool produce_Broad_GVCF = false;
  size_t segment_size = 10u*1024u*1024u; //in bytes = 10MB
  while((c=getopt_long(argc, argv, "j:w:A:p:O:s:", long_options, NULL)) >= 0)
  {
    switch(c)
    {
      case 'p':
        page_size = strtoull(optarg, 0, 10);
        std::cerr << "WARNING: page size is ignored for now\n";
        break;
      case 'O':
        output_format = std::move(std::string(optarg));
        break;
      case 'w':
        workspace = std::move(std::string(optarg));
        break;
      case 'A':
        array_name = std::move(std::string(optarg));
        break;
      case 's':
        segment_size = strtoull(optarg, 0, 10);
        break;
      case ARGS_IDX_SKIP_QUERY_ON_ROOT:
        skip_query_on_root = true;
        break;
      case ARGS_IDX_PRODUCE_BROAD_GVCF:
        produce_Broad_GVCF = true;
        do_range_query = false;
        break;
      case 'j':
        json_config_file = std::move(std::string(optarg));
        break;
      default:
        std::cerr << "Unknown command line argument\n";
        exit(-1);
    }
  }
  //Use VariantQueryConfig to setup query info
  VariantQueryConfig query_config;
#ifdef HTSDIR
  VCFAdapter vcf_adapter;
#endif
  //If JSON file specified, read workspace, array_name, rows/columns/fields to query from JSON file
  if(json_config_file != "")
  {
    RunConfig* run_config_ptr = 0;
    RunConfig range_query_run_config;
#if defined(HTSDIR) && defined(BCFTOOLSDIR)
    VCFAdapterRunConfig scan_run_config;
#endif
    if(do_range_query)
    {
      range_query_run_config.read_from_file(json_config_file, query_config, my_world_mpi_rank);
      run_config_ptr = &range_query_run_config;
    }
    else
      if(produce_Broad_GVCF)
      {
#if defined(HTSDIR) && defined(BCFTOOLSDIR)
        scan_run_config.read_from_file(json_config_file, query_config, vcf_adapter, output_format, my_world_mpi_rank);
        run_config_ptr = static_cast<RunConfig*>(&scan_run_config);
#else
        std::cerr << "Cannot produce Broad's combined GVCF without htslib and bcftools. Re-compile with HTSDIR and BCFTOOLSDIR variables set\n";
        exit(-1);
#endif
      }
    ASSERT(run_config_ptr);
    workspace = run_config_ptr->m_workspace;
    array_name = run_config_ptr->m_array_name;
  }
  else
  {
    if( optind + 2 > argc ) {
      std::cerr << std::endl<< "ERROR: Invalid number of arguments" << std::endl << std::endl;
      std::cout << "Usage: " << argv[0] << "  ( -j <json_config_file> | -w <workspace> -A <array name> <start> <end> ) [ -O <output_format> -p <page_size> ]" << std::endl;
      return -1;
    }
    uint64_t start = std::stoull(std::string(argv[optind]));
    uint64_t end = std::stoull(std::string(argv[optind+1])); 
    query_config.set_attributes_to_query(std::vector<std::string>{"REF", "ALT", "BaseQRankSum", "AD", "PL"});
    query_config.add_column_interval_to_query(start, end);
    if(produce_Broad_GVCF)
    {
      std::cerr << "To produce Broad's combined GVCF, you need to pass parameters through a JSON file, exiting\n";
      exit(-1);
    }
  }
  if(workspace == "" || array_name == "")
  {
    std::cerr << "Missing workspace(-w) or array name (-A)\n";
    return -1;
  }
#ifdef USE_GPERFTOOLS
  ProfilerStart("gprofile.log");
#endif
#if VERBOSE>0
  std::cerr << "Segment size: "<<segment_size<<" bytes\n";
#endif
  /*Create storage manager*/
  StorageManager sm(workspace, segment_size);
  /*Create query processor*/
  VariantQueryProcessor qp(&sm, array_name);
  qp.do_query_bookkeeping(qp.get_array_schema(), query_config);
  if(do_range_query)
    run_range_query(qp, query_config, output_format, num_mpi_processes, my_world_mpi_rank, skip_query_on_root);
#if defined(HTSDIR) && defined(BCFTOOLSDIR)
  else
    if(produce_Broad_GVCF)
      scan_and_produce_Broad_GVCF(qp, query_config, vcf_adapter, num_mpi_processes, my_world_mpi_rank, skip_query_on_root);
#endif
#ifdef USE_GPERFTOOLS
  ProfilerStop();
#endif

  MPI_Finalize();
  sm.close_array(qp.get_array_descriptor());
  return 0;
}
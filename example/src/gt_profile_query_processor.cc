#include <iostream>
#include "command_line.h"
#include "loader.h"
#include<math.h>
#include "query_variants.h"
#include "variant_operations.h"

void GenotypeColumn(VariantQueryProcessor& qp, GTProfileStats* stats, const StorageManager::ArrayDescriptor* ad_gVCF,
    uint64_t column, std::ostream& output_stream)
{
  VariantQueryConfig query_config;
  query_config.set_attributes_to_query(std::vector<std::string>{"REF", "ALT", "PL"});
  //Add interval to query - begin, end
  query_config.add_column_interval_to_query(column, column);
  qp.do_query_bookkeeping(ad_gVCF, query_config);
  /*Get one column from array*/ 
  GTColumn* gt_column = 0;
  //qp.gt_get_column(ad_gVCF, query_config, stats);
  //Do dummy genotyping operation
  VariantOperations::do_dummy_genotyping(gt_column, output_stream);
  delete gt_column;
}

int main(int argc, char** argv) {
  CommandLineOpts cl;
  parse_command_line(argc, argv, cl);
  if(cl.m_workspace == 0 || cl.m_array_name == 0)
  {
    std::cerr << "Missing workspace|array_name\n";
    exit(-1);
  }
  // Create storage manager
  // The input is the path to its workspace (the path must exist).
  StorageManager sm(cl.m_workspace);
  // Open arrays in READ mode
  const StorageManager::ArrayDescriptor* ad_gVCF = 
    sm.open_array(cl.m_array_name);
  // Create query processor
  // The first input is the path to its workspace (the path must exist).
  VariantQueryProcessor qp(cl.m_workspace, sm, ad_gVCF);
  //Setup query config
  VariantQueryConfig query_config;
  query_config.set_attributes_to_query(std::vector<std::string>{"REF", "ALT", "PL"});
  qp.do_query_bookkeeping(ad_gVCF, query_config);
  //Iterate over all tiles
  qp.iterate_over_all_tiles(ad_gVCF, query_config);
#ifdef DO_PROFILING
  printf("COORDS,END,REF,ALT,PL,OFFSETS,NULL\n");
  printf("%.2lf,",((double)g_num_tiles_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_COORDINATES_IDX)])/g_num_segments_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_COORDINATES_IDX)]);
  printf("%.2lf,",((double)g_num_tiles_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_END_IDX)])/g_num_segments_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_END_IDX)]);
  printf("%.2lf,",((double)g_num_tiles_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_REF_IDX)])/g_num_segments_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_REF_IDX)]);
  printf("%.2lf,",((double)g_num_tiles_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_ALT_IDX)])/g_num_segments_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_ALT_IDX)]);
  printf("%.2lf,",((double)g_num_tiles_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_PL_IDX)])/g_num_segments_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_PL_IDX)]);
  printf("%.2lf,",((double)g_num_tiles_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_OFFSETS_IDX)])/g_num_segments_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_OFFSETS_IDX)]);
  printf("%.2lf\n",((double)g_num_tiles_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_NULL_IDX)])/g_num_segments_loaded[qp.get_schema_idx_for_known_field_enum(GVCF_NULL_IDX)]);
#endif
  sm.close_array(ad_gVCF);
  
  return 0;
}

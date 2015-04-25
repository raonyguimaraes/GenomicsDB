#include <algorithm>
#include "variant_query_config.h"

using namespace std;

bool ColumnRangeCompare(const ColumnRange& x, const ColumnRange& y)
{
  return (x.first < y.first);
}

void VariantQueryConfig::set_rows_to_query(const vector<int64_t>& rowIdxVec)
{
  m_query_rows.resize(rowIdxVec.size());
  for(auto i=0u;i<rowIdxVec.size();++i)
    m_query_rows[i] = rowIdxVec[i];
  std::sort(m_query_rows.begin(), m_query_rows.end());    //useful in querying
  m_query_all_rows = false;
}

void VariantQueryConfig::add_column_interval_to_query(const int64_t colBegin, const int64_t colEnd)
{
  m_query_column_intervals.push_back(make_pair(colBegin, colEnd));
  std::sort(m_query_column_intervals.begin(), m_query_column_intervals.end(), ColumnRangeCompare);
}

void VariantQueryConfig::setup_array_row_idx_to_query_row_idx_map()
{
  if(m_query_all_rows)  //if querying all rows, don't even bother setting up map
    return;
  m_array_row_idx_to_query_row_idx.resize(get_num_rows_in_array());
  for(auto i=0ull;i<get_num_rows_in_array();++i)
    m_array_row_idx_to_query_row_idx[i] = UNDEFINED_NUM_ROWS_VALUE;     //invalid value
  for(auto i=0ull;i<m_query_rows.size();++i)
  {
    if(m_query_rows[i] < 0 || m_query_rows[i] >= get_num_rows_in_array())
      throw OutOfBoundsQueryException("Queried row index "+std::to_string(m_query_rows[i])+" is out of bounds");
    m_array_row_idx_to_query_row_idx[m_query_rows[i]] = i;
  }
}

void VariantQueryConfig::reorder_query_fields()
{
  auto special_field_names = vector<string>{ "COORDINATES", "END", "NULL", "OFFSETS", "ALT" };
  m_first_normal_field_query_idx = 0u;
  for(auto i=0u;i<special_field_names.size();++i)
  {
    unsigned query_idx = 0u;
    auto& curr_field_name = special_field_names[i];
    if(get_query_idx_for_name(curr_field_name, query_idx))
    {
      assert(query_idx >= m_first_normal_field_query_idx);
      if(query_idx > m_first_normal_field_query_idx) // == implies already in right place
      {
        auto& other_field_name = m_query_attributes_names[m_first_normal_field_query_idx];
        //Before swap, update name mappings
        m_query_attribute_name_to_query_idx[curr_field_name] = m_first_normal_field_query_idx;
        m_query_attribute_name_to_query_idx[other_field_name] = query_idx;
        //Swap positions in schema idx and attribute names vector
        std::swap(m_query_attributes_schema_idxs[query_idx], m_query_attributes_schema_idxs[m_first_normal_field_query_idx]);
        std::swap(m_query_attributes_names[query_idx], m_query_attributes_names[m_first_normal_field_query_idx]);
        //Now other_field_name can no longer be used
      }
      ++m_first_normal_field_query_idx;
    }
  }
}

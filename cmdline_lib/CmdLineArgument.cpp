
#include "CmdLineArgument.h"

namespace udr {
namespace cmdline {

CmdLineArgument::CmdLineArgument(const std::string & long_name) : 
  CmdLineParameter(long_name)
{
}

CmdLineArgument & CmdLineArgument::default_value(const std::string & default_value)
{
  m_default_value_str = default_value;
  return (*this);
}

unsigned int CmdLineArgument::counter() const
{
  return static_cast<unsigned int>(m_value_str_list.size());
}

void CmdLineArgument::m_process_tokens(const parsing_data_t & data)
{
  if (!data.name_found)
    throw std::runtime_error("Name not found on cmdline");

  if (!data.value_found)
    throw std::runtime_error("Value not found on cmdline");
  
  m_value_str_list.push_back(data.value);
}



} // namepspace cmdline
} // namespace udr

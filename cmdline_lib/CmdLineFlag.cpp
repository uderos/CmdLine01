#include <iostream>
#include "CmdLineFlag.h"

namespace udr {
namespace cmdline {

CmdLineFlag::CmdLineFlag(const std::string & long_name) : 
  CmdLineParameter(long_name),
  m_counter(0)
{
}

unsigned int CmdLineFlag::counter() const
{
  return m_counter;
}

void CmdLineFlag::m_process_tokens(const parsing_data_t & data)
{
  if (!data.name_found)
    throw std::runtime_error("Name not found on cmdline");

  if (data.value_found)
    throw std::runtime_error("Unexpected value found");
  
  ++m_counter;
}

} // namepspace cmdline
} // namespace udr


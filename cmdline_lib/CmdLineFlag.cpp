#include <iostream>
#include "CmdLineFlag.h"

namespace udr {
namespace cmdline {

CmdLineFlag::CmdLineFlag(const std::string & long_name) : 
  CmdLineParameter(long_name),
  m_counter(0)
{
}

CmdLineParameter & CmdLineFlag::default_value(const std::string & default_value)
{
  std::ostringstream oss;
  oss << "CmdLine: Parameter '" << m_get_long_name() << " does not support default values" << std::endl;
  throw std::runtime_error(oss.str());
}

unsigned int CmdLineFlag::counter() const
{
  return m_counter;
}

bool CmdLineFlag::has_value(const std::size_t /*idx = 0*/) const
{
  return false;
}

const std::string & CmdLineFlag::get_value_str(const std::size_t /*idx=0*/) const
{ 
  std::ostringstream oss;
  oss << "CmdLine: Parameter '" << m_get_long_name() << " does not supprt values" << std::endl;
  throw std::runtime_error(oss.str());
}

void CmdLineFlag::m_process_tokens(const parsing_data_t & data)
{
  if (!data.name_found)
    throw std::runtime_error("Name not found on cmdline");

  if (data.value_found)
    throw std::runtime_error("Unexpected value found");
  
  ++m_counter;
}

void CmdLineFlag::m_help_string(std::ostream & os) const
{
  ;
}

bool CmdLineFlag::m_value_parsing_required() const
{
  return false;
}

} // namepspace cmdline
} // namespace udr


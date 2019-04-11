
#include "CmdLineArgument.h"

namespace udr {
namespace cmdline {

CmdLineArgument::CmdLineArgument(const std::string & long_name) : 
  CmdLineParameter(long_name)
{
}

CmdLineParameter & CmdLineArgument::default_value(const std::string & default_value)
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

const std::string & CmdLineArgument::get_value_str(const std::size_t idx /*=0*/) const
{
  if (idx < m_value_str_list.size())
    return m_value_str_list[idx];

  if ((idx == 0) && (!m_default_value_str.empty()))
    return m_default_value_str;

  std::ostringstream oss;
  oss << "CmdLine: Value_" << idx << " not found for parameter " << m_get_long_name();
  throw std::runtime_error(oss.str());
}

bool CmdLineArgument::has_value(const std::size_t idx /*=0*/) const
{
  const bool has_value = (idx < m_value_str_list.size()) ||
                         ((idx == 0) && (!m_default_value_str.empty()));
  return has_value;
                         
}

void CmdLineArgument::m_help_string(std::ostream & os) const
{
  os << " value";
  if (!m_default_value_str.empty())
    os << "=" << m_default_value_str;
}

bool CmdLineArgument::m_value_parsing_required() const
{
  return true;
}


} // namepspace cmdline
} // namespace udr

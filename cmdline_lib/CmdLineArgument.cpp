
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
  const std::string * value_str_ptr = nullptr;

  if (idx < m_value_str_list.size())
    value_str_ptr = &(m_value_str_list[idx]);
  else if ((idx == 0) && (!m_default_value_str.empty()))
    value_str_ptr = &(m_default_value_str);

  if (!value_str_ptr)
  {
    std::ostringstream oss;
    oss << "CmdLine: Value_" << idx << " not found for parameter " << m_get_long_name();
    throw std::runtime_error(oss.str());
  }

  return (*value_str_ptr);
}

bool CmdLineArgument::has_value(const std::size_t idx /*=0*/) const
{
  const bool has_value = (idx < m_value_str_list.size()) ||
                         ((idx == 0) && (!m_default_value_str.empty()));
  return has_value;
                         
}



} // namepspace cmdline
} // namespace udr

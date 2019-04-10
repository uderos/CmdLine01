#include <sstream>
#include <stdexcept>
#include "CmdLineParameter.h"

namespace udr {
namespace cmdline {

CmdLineParameter::CmdLineParameter(const std::string & long_name) : 
  m_long_name(long_name),
  m_mandatory(false),
  m_global(false)
{
}

const std::string & CmdLineParameter::m_get_long_name() const
{
  return m_long_name;
}

CmdLineParameter & CmdLineParameter::short_name(const std::string & short_name)
{
  m_short_name = short_name;
  return (*this);
}

CmdLineParameter & CmdLineParameter::mandatory()
{
  m_mandatory = true;
  return (*this);
}

bool CmdLineParameter::is_mandatory() const
{
  return m_mandatory;
}

CmdLineParameter & CmdLineParameter::global()
{
  m_global = true;
  return (*this);
}

bool CmdLineParameter::is_global() const
{
  return m_global;
}

bool CmdLineParameter::parse(std::queue<std::string> & arg_queue)
{
  if (arg_queue.empty()) return false;

  try
  {
    const parsing_data_t data = m_parse_tokens(arg_queue);

    if (data.name_found)
    {
      m_process_tokens(data);
    }
  
    return data.name_found;
  }
  catch (std::exception & exh)
  {
    std::ostringstream oss;
    oss << "PARSING FAILURE"
        << " Paramater: " << m_long_name
        << " Error: " << exh.what();
    throw std::runtime_error(oss.str());
  }
}

CmdLineParameter::parsing_data_t 
CmdLineParameter::m_parse_tokens(std::queue<std::string> & arg_queue) const
{
  if (arg_queue.empty()) return parsing_data_t();

  const std::string long_name = std::string("--") + m_long_name;
  const std::string short_name = (m_short_name.empty() ? m_short_name : std::string("-") + m_short_name);

  parsing_data_t parsing_data;
  std::string::size_type value_idx = std::string::npos;

  const auto long_name_idx = arg_queue.front().find(long_name);

  const auto short_name_idx = (short_name.empty() ? 
      std::string::npos : arg_queue.front().find(short_name));

  if (long_name_idx != std::string::npos)
  {
    parsing_data.name_found = true;
    const auto name_len = long_name.size();
    if (name_len < arg_queue.front().size())
      value_idx = arg_queue.front().find_first_of('=', name_len);
    if ((value_idx != std::string::npos) && 
        (arg_queue.front()[value_idx] == '='))
      ++value_idx;
  }
  else if (short_name_idx != std::string::npos)
  {
    parsing_data.name_found = true;
    if (m_value_parsing_required())
    {
      arg_queue.pop();
      if (!arg_queue.empty())
        value_idx = 0;
    }
  }

  if (m_value_parsing_required() &&
      parsing_data.name_found && 
      (value_idx != std::string::npos) &&
      (!arg_queue.empty())) // redundant 
  {
    if (value_idx < arg_queue.front().size())
    {
      parsing_data.value = arg_queue.front().substr(value_idx);
      parsing_data.value_found = true;
    }
    else
    {
      throw std::runtime_error("Value parsing error");
    }
  }

  if (parsing_data.name_found && (!arg_queue.empty()))
    arg_queue.pop();

  return parsing_data;
}

std::string CmdLineParameter::help_string() const
{
  std::ostringstream oss;

  oss << (m_mandatory ? '<' : '[');

  oss << "--" << m_long_name;

  if (!m_short_name.empty())
    oss << " (-" << m_short_name << ")";

  m_help_string(oss);

  oss << (m_mandatory ? '>' : ']');

  return oss.str();
}


} // namepspace cmdline
} // namespace udr

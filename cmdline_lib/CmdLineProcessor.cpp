#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include "CmdLineProcessor.h"

namespace udr {
namespace cmdline {

CmdLineProcessor::CmdLineProcessor()
{
}

CmdLineProcessor::~CmdLineProcessor()
{
}

CmdLineArgument & CmdLineProcessor::AddArgument(const std::string & long_name)
{
  return m_add_parameter<CmdLineArgument>(long_name);
}

CmdLineFlag & CmdLineProcessor::AddFlag(const std::string & long_name)
{
  return m_add_parameter<CmdLineFlag>(long_name);
}

std::vector<std::string> CmdLineProcessor::parse(const int argc, const char *argv[])
{
  const auto unprocessed_list = m_parse_cmdline(argc, argv);
  
  if (! m_has_global_params())
    m_check_missing_params();

  return unprocessed_list;
}

bool CmdLineProcessor::has_value(const std::string & long_name,
                                 const std::size_t idx /*=0*/) const
{
  return m_get_parameter(long_name).has_value(idx);
}

std::vector<std::string> CmdLineProcessor::m_parse_cmdline(const int argc, const char *argv[])
{
  std::queue<std::string> arg_queue;
  for (int i = 1; i < argc; ++i)
    arg_queue.emplace(argv[i]);

  std::vector<std::string> unprocessed_list;
  while(!arg_queue.empty())
  {
    bool processed = false;
    for (const auto & elem : m_param_map)
    {
      processed = elem.second->parse(arg_queue);
      if (processed) break;
    }
    if (!processed)
    {
      unprocessed_list.push_back(arg_queue.front());
      arg_queue.pop();
    }
  }

  return unprocessed_list;
}

bool CmdLineProcessor::m_has_global_params() const
{
  for (const auto & elem : m_param_map)
    if (elem.second->counter() && elem.second->is_global())
      return true;

  return false;
}

void CmdLineProcessor::m_check_missing_params() const
{
  for (const auto & elem : m_param_map)
  {
    if (elem.second->is_mandatory() && (elem.second->counter() == 0))
    {
      std::ostringstream oss;
      oss << "CmdLine: Mandatory parameter '" << elem.first << "' not found";
      throw std::runtime_error(oss.str());
    }
  }
}

const CmdLineParameter & CmdLineProcessor::operator[](const std::string & long_name) const
{
  return m_get_parameter(long_name);
}

const CmdLineParameter & CmdLineProcessor::m_get_parameter(const std::string & long_name) const
{
  const auto it = m_param_map.find(long_name);
  if (it == m_param_map.end())
  {
    std::ostringstream oss;
    oss << "CmdLine: Requested parameter '" << long_name << "' not defined";
    throw std::runtime_error(oss.str());
  }

  const auto & param_ptr = it->second;
  return *param_ptr;
}

std::string CmdLineProcessor::help_string(const std::string & header) const
{
  std::ostringstream oss;
  oss << header << std::endl;
  for (const auto & elem : m_param_map)
    oss << '\t' << elem.second->help_string() << std::endl;
  return oss.str();
}

std::string CmdLineProcessor::to_string() const
{
  std::string separator;
  std::ostringstream oss;
  for (const auto & elem : m_param_map)
  {
    for (std::size_t idx = 0; idx < elem.second->counter(); ++idx)
    {
      oss << separator << "--" << elem.first;
      if (elem.second->has_value(idx))
          oss << "=" << elem.second->get_value_str(idx);
      separator = " ";
    }
   }
  return oss.str();
}

} // namepspace cmdline
} // namespace udr

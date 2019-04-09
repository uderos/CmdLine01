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
  
  for (const auto & elem : m_param_map)
  {
    if (elem.second->is_mandatory() && (elem.second->counter() == 0))
    {
      std::ostringstream oss;
      oss << "CmdLine: Mandatory parameter '" << elem.first << "' not found";
      throw std::runtime_error(oss.str());
    }
  }

  return unprocessed_list;
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

std::string CmdLineProcessor::to_string() const // debug purpose only
{
  std::ostringstream oss;
  oss << "CmdLineProcessor: n=" << m_param_map.size() << std::endl;
  for (const auto & elem : m_param_map)
  {
    std::string separator;
    const unsigned int n = elem.second->counter();

    oss << "\t" << elem.first << " c=" << elem.second->counter();

    if (elem.second->counter())
    {
      oss << " values: ";
      for (unsigned int idx = 0; idx < n; ++idx)
      {
        if (elem.second->has_value(idx))
        {
          oss << separator << "'" << elem.second->get_value_str(idx) << "'";
          separator = "|";
        }
      }
    }

    oss << std::endl;
  }

  return oss.str();
}

std::string CmdLineProcessor::help_string(const std::string & header) const
{
  std::ostringstream oss;
  oss << header << std::endl;
  for (const auto & elem : m_param_map)
    oss << '\t' << elem.second->help_string() << std::endl;
  return oss.str();
}

} // namepspace cmdline
} // namespace udr

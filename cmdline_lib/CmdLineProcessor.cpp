#include <iostream>
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

void CmdLineProcessor::parse(const int argc, const char *argv[])
{
  for (int i = 0; i < argc; ++i)
  {
    const std::string input_str(argv[i]);

    for (const auto & elem : m_param_map)
    {
      std::cout << "UBEDEBUG Passing '" << input_str << "' to " << elem.first << std::endl; // UBEDEBUG
      const bool processed = elem.second->parse(input_str);
      if (processed) break;
    }
  }
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
    oss << "\t" << elem.first << " c=" << elem.second->counter() << std::endl;
  }

  return oss.str();
}

} // namepspace cmdline
} // namespace udr

#ifndef UDR_CMDLINE_CLDLINE_PROCESSOR_H
#define UDR_CMDLINE_CLDLINE_PROCESSOR_H

#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include "CmdLineArgument.h"
#include "CmdLineFlag.h"

namespace udr {
namespace cmdline {

class CmdLineProcessor
{
  public:
    CmdLineProcessor();
    virtual ~CmdLineProcessor();

    // Setup
    CmdLineArgument & AddArgument(const std::string & long_name);
    CmdLineFlag & AddFlag(const std::string & long_name);

    // Infrastructure
    void parse(const int argc, const char *argv[]);

    const CmdLineParameter & operator[](const std::string & long_name) const;
    template <typename T> T get_value(const std::string & long_name,
                                      const std::size_t idx = 0) const;

    std::string to_string() const; // debug purpose only

  protected:

  private:

    using param_ptr_t = std::unique_ptr<CmdLineParameter>;
    using param_map_t = std::map<std::string, param_ptr_t>;
    param_map_t m_param_map;

    template <typename PARAM_T> 
    PARAM_T & m_add_parameter(const std::string & long_name);

    const CmdLineParameter & m_get_parameter(const std::string & long_name) const;
};

template <typename PARAM_T> 
PARAM_T & CmdLineProcessor::m_add_parameter(const std::string & long_name)
{
  if (m_param_map.find(long_name) != m_param_map.end())
  {
    std::ostringstream oss;
    oss << "Duplicated CmdLine argument: " << long_name;
    throw std::runtime_error(oss.str());
  }

  PARAM_T * new_param_ptr = new PARAM_T(long_name);
  m_param_map[long_name] = std::unique_ptr<PARAM_T>(new_param_ptr);
  return (*new_param_ptr);
}

template <typename T> 
T CmdLineProcessor::get_value(const std::string & long_name,
                              const std::size_t idx /*= 0*/) const
{
  const CmdLineParameter & p = m_get_parameter(long_name);

  /**
  const auto it = m_param_map.find(long_name);
  if (it == m_param_map.end())
  {
    std::ostringstream oss;
    oss << "CmdLine: Requested parameter '" << long_name << "' not defined";
    throw std::runtime_error(oss.str());
  }
  */

  const CmdLineArgument * arg_ptr = dynamic_cast<const CmdLineArgument *>(&p);
  if (! arg_ptr)
  {
    std::ostringstream oss;
    oss << "CmdLine: Requested parameter '" << long_name << "' is not an argument";
    throw std::runtime_error(oss.str());
  }

  return arg_ptr->get_value<T>(idx);
}


} // namepspace cmdline
} // namespace udr
#endif // UDR_CMDLINE_CLDLINE_PROCESSOR_H

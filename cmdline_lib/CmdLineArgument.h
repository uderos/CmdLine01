#ifndef UDR_CMDLINE_CLDLINE_ARGUMENT_H
#define UDR_CMDLINE_CLDLINE_ARGUMENT_H

#include <typeinfo>
#include <vector>
#include "CmdLineParameter.h"

namespace udr {
namespace cmdline {

class CmdLineArgument : public CmdLineParameter
{
  public:
    CmdLineArgument(const std::string & long_name);
    virtual ~CmdLineArgument() = default;

    CmdLineArgument & default_value(const std::string & default_value);

    // Queries
    unsigned int counter() const;
    template <typename T> T get_value(const std::size_t idx = 0) const;

  private:
    std::string m_default_value_str;
    std::vector<std::string> m_value_str_list;

    virtual void m_process_tokens(const parsing_data_t & data);
};

template <typename T> 
T CmdLineArgument::get_value(const std::size_t idx /*=0*/) const
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

  T value;
  std::istringstream iss(*value_str_ptr);
  iss >> value;

  if (!iss)
  {
    std::ostringstream oss;
    oss << "CmdLine: Argument:'" << m_get_long_name() << "' conversion failure"
        << " idx:" << idx
        << " str='" << (*value_str_ptr) << "'"
        << " type=" << typeid(T).name();
    throw std::runtime_error(oss.str());
  }

  return value;
}

} // namepspace cmdline
} // namespace udr
#endif // UDR_CMDLINE_CLDLINE_ARGUMENT_H

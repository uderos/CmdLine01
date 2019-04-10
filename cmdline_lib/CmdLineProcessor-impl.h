#ifndef UDR_CMDLINE_CLDLINE_PROCESSOR_IMPL_H
#define UDR_CMDLINE_CLDLINE_PROCESSOR_IMPL_H

namespace udr {
namespace cmdline {


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
  const std::string & value_str =p.get_value_str(idx);

  T value;
  std::istringstream iss(value_str);
  iss >> value;

  if (!iss)
  {
    std::ostringstream oss;
    oss << "CmdLine: Argument:'" << long_name << "' conversion failure"
        << " idx:" << idx
        << " str='" << value_str << "'"
        << " type=" << typeid(T).name();
    throw std::runtime_error(oss.str());
  }

  return value;
}

} // namepspace cmdline
} // namespace udr

#endif // UDR_CMDLINE_CLDLINE_PROCESSOR_IMPL_H

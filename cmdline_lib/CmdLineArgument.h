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
    virtual bool has_value(const std::size_t idx = 0) const override;
    virtual const std::string & get_value_str(const std::size_t idx = 0) const override;

  private:
    std::string m_default_value_str;
    std::vector<std::string> m_value_str_list;

    virtual void m_process_tokens(const parsing_data_t & data);
};

} // namepspace cmdline
} // namespace udr
#endif // UDR_CMDLINE_CLDLINE_ARGUMENT_H

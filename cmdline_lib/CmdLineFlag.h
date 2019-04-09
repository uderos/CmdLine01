#ifndef UDR_CMDLINE_CLDLINE_FLAG_H
#define UDR_CMDLINE_CLDLINE_FLAG_H

#include <vector>
#include "CmdLineParameter.h"

namespace udr {
namespace cmdline {

class CmdLineFlag : public CmdLineParameter
{
  public:
    CmdLineFlag(const std::string & long_name);
    virtual ~CmdLineFlag() = default;

    virtual CmdLineParameter & default_value(const std::string & default_value) override;

    // Queries
    virtual bool has_value(const std::size_t idx = 0) const override;
    virtual const std::string & get_value_str(const std::size_t idx = 0) const override;
    virtual unsigned int counter() const;

  private:
    unsigned int m_counter;

    virtual bool m_value_parsing_required() const override;
    virtual void m_process_tokens(const parsing_data_t & data);
    virtual void m_help_string(std::ostream & os) const override;
};


} // namepspace cmdline
} // namespace udr
#endif // UDR_CMDLINE_CLDLINE_FLAG_H


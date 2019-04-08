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

    // Queries
    virtual unsigned int counter() const;

  private:
    unsigned int m_counter;

    virtual void m_process_tokens(const parsing_data_t & data);
};


} // namepspace cmdline
} // namespace udr
#endif // UDR_CMDLINE_CLDLINE_FLAG_H


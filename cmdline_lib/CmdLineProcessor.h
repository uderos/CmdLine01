#ifndef UDR_CMDLINE_CLDLINE_PROCESSOR_H
#define UDR_CMDLINE_CLDLINE_PROCESSOR_H

#include <map>
#include <memory>
#include <vector>

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

    // Operations
    std::vector<std::string> parse(const int argc, const char *argv[]);

    // Queries
    const CmdLineParameter & operator[](const std::string & long_name) const;
    bool has_value(const std::string & long_name,
                   const std::size_t idx = 0) const;
    template <typename T> T get_value(const std::string & long_name,
                                      const std::size_t idx = 0) const;

    // Infrastructure and utils
    std::string help_string(const std::string & header) const;
    std::string to_string() const;


  private:

    using param_ptr_t = std::unique_ptr<CmdLineParameter>;
    using param_map_t = std::map<std::string, param_ptr_t>;
    param_map_t m_param_map;

    template <typename PARAM_T> 
    PARAM_T & m_add_parameter(const std::string & long_name);

    const CmdLineParameter & m_get_parameter(const std::string & long_name) const;
    std::vector<std::string> m_parse_cmdline(const int argc, const char *argv[]);
    bool m_has_global_params() const;
    void m_check_missing_params() const;
};

// Template and inline method implementations
#include "CmdLineProcessor-impl.h"

} // namepspace cmdline
} // namespace udr

#endif // UDR_CMDLINE_CLDLINE_PROCESSOR_H

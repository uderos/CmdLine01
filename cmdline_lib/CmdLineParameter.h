#ifndef UDR_CMDLINE_CLDLINE_PARAM_H
#define UDR_CMDLINE_CLDLINE_PARAM_H

#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>

namespace udr {
namespace cmdline {

class CmdLineParameter
{
  public:
    virtual ~CmdLineParameter() = default;

    // Set properties
    CmdLineParameter & short_name(const std::string & short_name);
    CmdLineParameter & mandatory();
    virtual CmdLineParameter & default_value(const std::string & default_value);

    // Queries
    const bool is_mandatory() const;
    virtual unsigned int counter() const = 0;
    virtual bool has_value(const std::size_t idx = 0) const;
    virtual const std::string & get_value_str(const std::size_t idx = 0) const;

    // Infrastructure
    bool parse(std::queue<std::string> & arg_queue);

  protected:

    CmdLineParameter(const std::string & long_name);

    struct parsing_data_t
    {
      bool name_found;
      bool value_found;
      std::string value;
      parsing_data_t() : name_found(false), value_found(false) {};
      ~parsing_data_t() = default;
    };

    const std::string & m_get_long_name() const;

  private:
    const std::string m_long_name;
    std::string m_short_name;
    bool m_mandatory;

    parsing_data_t m_parse_tokens(std::queue<std::string> & arg_queue) const;
    virtual void m_process_tokens(const parsing_data_t & data) = 0;

};

} // namepspace cmdline
} // namespace udr
#endif // UDR_CMDLINE_CLDLINE_PARAM_H

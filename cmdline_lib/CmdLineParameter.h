#ifndef UDR_CMDLINE_CLDLINE_PARAM_H
#define UDR_CMDLINE_CLDLINE_PARAM_H

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

    // Queries
    virtual unsigned int counter() const = 0;

    // Infrastructure
    bool parse(const std::string & input_str);

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
    //unsigned int m_counter;
    
//    bool m_name_match(const std::string & input_str, 
//                      const std::string & param_name) const;
    parsing_data_t m_parse_tokens(const std::string & input_str) const;
    virtual void m_process_tokens(const parsing_data_t & data) = 0;

};

} // namepspace cmdline
} // namespace udr
#endif // UDR_CMDLINE_CLDLINE_PARAM_H

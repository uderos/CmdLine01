#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "cmdline_lib/CmdLineProcessor.h"

using uint = unsigned int;
using str_list_t = std::vector<std::string>;

static void f_cmdline_config(udr::cmdline::CmdLineProcessor & cmdl)
{
  cmdl.AddFlag("version").short_name("v");
  cmdl.AddFlag("help").short_name("h").global();
  cmdl.AddArgument("numerator").short_name("n").mandatory();
  cmdl.AddArgument("denominator").short_name("d").default_value("1");
  cmdl.AddArgument("arg").short_name("a").default_value("1");
  cmdl.AddArgument("input-file").short_name("f");
}

static void f_print_values(const str_list_t & names,
                           const udr::cmdline::CmdLineProcessor & cmdl)
{
  static constexpr std::size_t NUM_VALUES = 3;
  for (const auto & name : names)
  {
    for (std::size_t idx = 0; idx < NUM_VALUES; ++idx)
    {
      const bool found = (idx < cmdl[name].counter());
      const bool has_value = cmdl[name].has_value(idx);
      std::cout << "Parameter '" << name << "' idx=" << idx;
      std::cout << (found ? " found" : " (not found)");
      if (has_value)
        std::cout << " value='" << cmdl[name].get_value_str(idx) << "'";
      else
        std::cout << " (no value)";
      std::cout << std::endl;
    }
  }
}

int main(const int argc, const char *argv[])
{
  try
  {
    udr::cmdline::CmdLineProcessor cmdl;
    f_cmdline_config(cmdl);
    auto unprocessed = cmdl.parse(argc, argv);

    std::cout << "to_string: '" << cmdl.to_string() << "'" << std::endl;

    if (cmdl["help"].counter() > 0)
    {
      std::cout << "--------------------------\n";
      std::cout << cmdl.help_string("TEST03: " __DATE__ "-" __TIME__);
      std::cout << "--------------------------\n";
    }

    for (const auto u : unprocessed)
      std::cout << "Unprocessed parameter: " << u << std::endl;

    const str_list_t names { "version", "help", "numerator", 
                             "denominator", "arg", "input-file" };
    f_print_values(names, cmdl);

  }
  catch (const std::exception & exh)
  {
    std::cout << "UNEXPECTED EXCEPTION: " << exh.what() << std::endl;
    return 1;
  }

  return 0;
}


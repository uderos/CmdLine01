#include <iostream>
#include <stdexcept>

#include "cmdline_lib/CmdLineProcessor.h"

using uint = unsigned int;

static void f_cmdline_config(udr::cmdline::CmdLineProcessor & cmdl)
{
  cmdl.AddFlag("version").short_name("v");
  cmdl.AddFlag("help").short_name("h").global();
  cmdl.AddArgument("verbose").short_name("V").default_value("1");
  cmdl.AddArgument("numerator").short_name("n").mandatory();
  cmdl.AddArgument("denominator").short_name("d").default_value("1");
  cmdl.AddArgument("arg").short_name("a").default_value("1");
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
  }
  catch (const std::exception & exh)
  {
    std::cout << "UNEXPECTED EXCEPTION: " << exh.what() << std::endl;
    return 1;
  }

  return 0;
}


#include <iostream>
#include <stdexcept>

#include "cmdline_lib/CmdLineProcessor.h"

using uint = unsigned int;

static void f_cmdline_config(udr::cmdline::CmdLineProcessor & cmdl)
{
  cmdl.AddFlag("version");
  cmdl.AddArgument("verbose").short_name("v").default_value("1");
  cmdl.AddArgument("numerator").short_name("n").mandatory();
  cmdl.AddArgument("denominator").short_name("d").default_value("1");
}

int main(const int argc, const char *argv[])
{
  try
  {
    udr::cmdline::CmdLineProcessor cmdl;
    f_cmdline_config(cmdl);
    cmdl.parse(argc, argv);

    std::cout << "CMD_LINE: " << cmdl.to_string() << std::endl;
  }
  catch (const std::exception & exh)
  {
    std::cout << "UNEXPECTED EXCEPTION: " << exh.what() << std::endl;
    return 1;
  }

  return 0;
}


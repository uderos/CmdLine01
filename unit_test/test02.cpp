#include <iostream>
#include <stdexcept>

#include "cmdline_lib/CmdLineProcessor.h"

using uint = unsigned int;

static void f_test02()
{
  std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

  udr::cmdline::CmdLineProcessor cmdl;
  
  std::cout << "Adding parameters ..." << std::endl;
  cmdl.AddArgument("arg1").short_name("a");
  cmdl.AddFlag("flag1");

  const char * argv[] { "--flag1", "--arg1=11", "-a 22" };
  const int argc = sizeof(argv) / sizeof(argv[0]);

  std::cout << "Parsing command line ..." << std::endl;
  cmdl.parse(argc, argv);

  std::cout << "Dumping on stdout ..." << std::endl;
  std::cout << "cmdl=" << cmdl.to_string() << std::endl;

  std::cout << "Checking values ..." << std::endl;
  std::cout << "Number of flag1 flags=" << cmdl["flag1"].counter() << std::endl;
  std::cout << "arg1 value[0] = " << cmdl.get_value<int>(std::string("arg1")) << std::endl;
}


static void f_test01()
{
  std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

  udr::cmdline::CmdLineProcessor cmdl;
  
  std::cout << "Adding parameters ..." << std::endl;
  cmdl.AddArgument("arg1");
  cmdl.AddFlag("flag1");

  const char * argv[] { "--flag1", "--arg1=11", "aa", "bb", "--flag1" };
  const int argc = sizeof(argv) / sizeof(argv[0]);

  std::cout << "Parsing command line ..." << std::endl;
  cmdl.parse(argc, argv);

  std::cout << "Dumping on stdout ..." << std::endl;
  std::cout << "cmdl=" << cmdl.to_string() << std::endl;
}


int main()
{
  try
  {
    f_test01();
    f_test02();
  }
  catch (const std::exception & exh)
  {
    std::cout << "UNEXPECTED EXCEPTION: " << exh.what() << std::endl;
    return 1;
  }

  return 0;
}


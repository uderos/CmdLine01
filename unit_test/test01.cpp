#include <iostream>
#include <stdexcept>

#include "cmdline_lib/CmdLineArgument.h"
#include "cmdline_lib/CmdLineFlag.h"

using uint = unsigned int;

static void f_test02()
{
  std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

  { 
    udr::cmdline::CmdLineFlag p("param");
    const uint counter = p.counter();
    std::cout << "line_" << __LINE__ << " counter=" << counter << std::endl;
  }

  {
    udr::cmdline::CmdLineFlag p("param");
    p.parse("--param");
    const uint counter = p.counter();
    std::cout << "line_" << __LINE__ << " counter=" << counter << std::endl;
  }

  {
    udr::cmdline::CmdLineFlag p("param");
    p.short_name("p");
    p.parse("-p");
    const uint counter = p.counter();
    std::cout << "line_" << __LINE__ << " counter=" << counter << std::endl;
  }

  {
    udr::cmdline::CmdLineFlag p("param");
    p.short_name("p");
    p.parse("-p");
    p.parse("-param");
    p.parse("-p");
    p.parse("--qqqq");
    p.parse("-q");
    const uint counter = p.counter();
    std::cout << "line_" << __LINE__ << " counter=" << counter << std::endl;
  }

}


static void f_test01()
{
  std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

  { 
    udr::cmdline::CmdLineArgument p("param");
    p.default_value("123");
    const int v = p.get_value<int>();
    std::cout << "line_" << __LINE__ << " V=" << v << std::endl;
  }

  {
    udr::cmdline::CmdLineArgument p("param");
    p.parse("--param=234");
    const int v = p.get_value<int>();
    std::cout << "line_" << __LINE__ << " V=" << v << std::endl;
  }

  {
    udr::cmdline::CmdLineArgument p("param");
    p.short_name("p");
    p.parse("-p 345");
    const int v = p.get_value<int>();
    std::cout << "line_" << __LINE__ << " V=" << v << std::endl;
  }

  {
    udr::cmdline::CmdLineArgument p("param");
    p.short_name("p");
    p.parse("-p 4.56");
    const float v = p.get_value<float>();
    std::cout << "line_" << __LINE__ << " V=" << v << std::endl;
  }

  {
    udr::cmdline::CmdLineArgument p("bool_param");
    p.parse("--bool_param=1");
    const bool v = p.get_value<int>();
    std::cout << "line_" << __LINE__ << " V=" << v << std::endl;
  }

  try
  {
    udr::cmdline::CmdLineArgument p("param");
    p.parse("--param=QQQQ");
    const int v = p.get_value<int>();
    std::cout << "line_" << __LINE__ << " V=" << v << std::endl;
  }
  catch (const std::exception & exh)
  {
    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
  }

  {
    udr::cmdline::CmdLineArgument p("param");
    p.short_name("p");
    p.parse("-p 11");
    p.parse("-p 22");
    p.parse("-q 00");
    p.parse("-p 33");
    const int v1 = p.get_value<int>(0);
    const int v2 = p.get_value<int>(1);
    const int v3 = p.get_value<int>(2);
    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
    std::cout << "line_" << __LINE__ << " V1=" << v1 << std::endl;
    std::cout << "line_" << __LINE__ << " V2=" << v2 << std::endl;
    std::cout << "line_" << __LINE__ << " V3=" << v3 << std::endl;
  }

  try
  {
    udr::cmdline::CmdLineArgument p("param");
    p.short_name("p");
    p.parse("-p");
    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
  }
  catch (const std::exception & exh)
  {
    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
  }

  try
  {
    udr::cmdline::CmdLineArgument p("param");
    p.short_name("p");
    p.parse("-p ");
    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
  }
  catch (const std::exception & exh)
  {
    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
  }

  try
  {
    udr::cmdline::CmdLineArgument p("param");
    p.parse("--param");
    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
  }
  catch (const std::exception & exh)
  {
    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
  }

  try
  {
    udr::cmdline::CmdLineArgument p("param");
    p.parse("--param=");
    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
  }
  catch (const std::exception & exh)
  {
    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
  }

  try
  {
    udr::cmdline::CmdLineArgument p("param");
    p.parse("--param = 99");
    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
    std::cout << "line_" << __LINE__ << " v=" << p.get_value<int>() << std::endl;
  }
  catch (const std::exception & exh)
  {
    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
  }

  {
    udr::cmdline::CmdLineArgument p("param");
    p.parse("--param=XYZ");
    const std::string v = p.get_value<std::string>();
    std::cout << "line_" << __LINE__ << " V=" << v << std::endl;
  }

  {
    udr::cmdline::CmdLineArgument p("param");
    p.short_name("p");
    p.parse("-p xyz");
    const std::string v = p.get_value<std::string>();
    std::cout << "line_" << __LINE__ << " V=" << v << std::endl;
  }

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


#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "cmdline_lib/CmdLineArgument.h"
#include "cmdline_lib/CmdLineFlag.h"

using uint = unsigned int;
using arg_queue_t = std::queue<std::string>;

static arg_queue_t f_create_arg_queue(const std::vector<std::string> & arg_list)
{
  arg_queue_t arg_queue;
  for (const auto & arg : arg_list)
    arg_queue.push(arg);

  return arg_queue;
}

static void f_test02()
{
  std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

//  { 
//    udr::cmdline::CmdLineFlag p("param");
//    const uint counter = p.counter();
//    std::cout << "line_" << __LINE__ << " counter=" << counter << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineFlag p("param");
//    arg_queue_t arg_queue = f_create_arg_queue({"--param"});
//    p.parse(arg_queue);
//    const uint counter = p.counter();
//    std::cout << "line_" << __LINE__ << " counter=" << counter << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineFlag p("param");
//    p.short_name("p");
//    p.parse(f_create_arg_queue({"-p"}));
//    const uint counter = p.counter();
//    std::cout << "line_" << __LINE__ << " counter=" << counter << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineFlag p("param");
//    p.short_name("p");
//    p.parse("-p");
//    p.parse("-param");
//    p.parse("-p");
//    p.parse("--qqqq");
//    p.parse("-q");
//    const uint counter = p.counter();
//    std::cout << "line_" << __LINE__ << " counter=" << counter << std::endl;
//  }

}


static void f_test01()
{
  std::cout << "\n\n" << __FUNCTION__ << "() BEGIN" << std::endl;

//  { 
//    udr::cmdline::CmdLineArgument p("param");
//    p.default_value("123");
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.parse({"--param=234"});
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.short_name("p");
//    p.parse("-p 345");
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.short_name("p");
//    p.parse("-p 4.56");
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineArgument p("bool_param");
//    p.parse("--bool_param=1");
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }
//
//  try
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.parse("--param=QQQQ");
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }
//  catch (const std::exception & exh)
//  {
//    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.short_name("p");
//    p.parse("-p 11");
//    p.parse("-p 22");
//    p.parse("-q 00");
//    p.parse("-p 33");
//    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
//    std::cout << "line_" << __LINE__ << " Vstr0=" << p.get_value_str(0) << std::endl;
//    std::cout << "line_" << __LINE__ << " Vstr1=" << p.get_value_str(1) << std::endl;
//    std::cout << "line_" << __LINE__ << " Vstr2=" << p.get_value_str(2) << std::endl;
//  }
//
//  try
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.short_name("p");
//    p.parse("-p");
//    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
//  }
//  catch (const std::exception & exh)
//  {
//    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
//  }
//
//  try
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.short_name("p");
//    p.parse("-p ");
//    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
//  }
//  catch (const std::exception & exh)
//  {
//    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
//  }
//
//  try
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.parse("--param");
//    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
//  }
//  catch (const std::exception & exh)
//  {
//    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
//  }
//
//  try
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.parse("--param=");
//    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
//  }
//  catch (const std::exception & exh)
//  {
//    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
//  }
//
//  try
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.parse("--param = 99");
//    std::cout << "line_" << __LINE__ << " counter=" << p.counter() << std::endl;
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }
//  catch (const std::exception & exh)
//  {
//    std::cout << "Expected EXCEPTION: " << exh.what() << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.parse("--param=XYZ");
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }
//
//  {
//    udr::cmdline::CmdLineArgument p("param");
//    p.short_name("p");
//    p.parse("-p xyz");
//    std::cout << "line_" << __LINE__ << " Vstr=" << p.get_value_str() << std::endl;
//  }

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


cmake_minimum_required (VERSION 2.8.11)

set(SRC_FILES CmdLineParameter.cpp CmdLineArgument.cpp CmdLineFlag.cpp CmdLineProcessor.cpp)

add_library(cmdline_lib ${SRC_FILES})


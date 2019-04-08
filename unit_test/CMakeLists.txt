cmake_minimum_required (VERSION 2.8.11)

set(SRC_FILES_01 test01.cpp)
add_executable(test01 ${SRC_FILES_01})
TARGET_LINK_LIBRARIES(test01 cmdline_lib)

set(SRC_FILES_02 test02.cpp)
add_executable(test02 ${SRC_FILES_02})
TARGET_LINK_LIBRARIES(test02 cmdline_lib)


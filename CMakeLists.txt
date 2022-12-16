cmake_minimum_required(VERSION 3.24)
project(Mission)

set(CMAKE_CXX_STANDARD 14)

add_executable(Mission src/fnctns.cpp src/main.cpp src/mssn_rlztn.cpp src/object.cpp src/object.cpp hdrs/fnctns.h hdrs/mssn_rlztn.h hdrs/object.h)

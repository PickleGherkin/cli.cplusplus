cmake_minimum_required(VERSION 3.10)
project(CLI.CPlusPlus)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(main src/main.cpp src/options.cpp)

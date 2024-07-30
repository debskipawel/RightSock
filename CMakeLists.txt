cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

option(BUILD_EXAMPLES "Build example applications" OFF)

project(RightSock)

include(cmake/options.cmake)

add_subdirectory(RightSock)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

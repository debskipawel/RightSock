cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

option(BUILD_EXAMPLES "Build example applications" OFF)

project(right-sock)

include(cmake/options.cmake)

add_subdirectory(right-sock)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

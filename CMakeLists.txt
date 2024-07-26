cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(socket-lib)

include(cmake/options.cmake)

add_subdirectory(socket-library)

add_subdirectory(app-server)
add_subdirectory(app-client)

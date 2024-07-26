cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(socket-lib)

include(cmake/options.cmake)

add_subdirectory(socket-library)

if(WIN32)

  add_subdirectory(windows-server-app)
  add_subdirectory(windows-client-app)

elseif(LINUX)

  add_subdirectory(linux-app)

endif()

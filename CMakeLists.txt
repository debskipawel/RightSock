cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(socket-lib)

add_subdirectory(socket-library)

if(WIN32)

    add_subdirectory(windows-app)

elseif(LINUX)

    add_subdirectory(linux-app)

endif()

add_executable(bigass-server)

target_sources(bigass-server PRIVATE main.cpp)

target_link_libraries(bigass-server PUBLIC right-sock)

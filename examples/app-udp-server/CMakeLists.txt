add_executable(app-udp-server)

target_sources(app-udp-server PRIVATE main.cpp)

target_link_libraries(app-udp-server PUBLIC right-sock)

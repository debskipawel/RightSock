add_executable(app-udp-client)

target_sources(app-udp-client PRIVATE main.cpp)

target_link_libraries(app-udp-client PUBLIC right-sock)

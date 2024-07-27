add_executable(app-tcp-client)

target_sources(app-tcp-client PRIVATE main.cpp)

target_link_libraries(app-tcp-client PUBLIC right-sock)

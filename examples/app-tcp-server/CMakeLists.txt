add_executable(app-tcp-server)

target_sources(app-tcp-server PRIVATE main.cpp)

target_link_libraries(app-tcp-server PUBLIC right-sock)

add_executable(app-server)

target_sources(app-server PRIVATE main.cpp)

target_link_libraries(app-server PUBLIC socket-library)

add_executable(windows-server-app)

target_sources(windows-server-app PRIVATE main.cpp)

target_link_libraries(windows-server-app PUBLIC socket-library)

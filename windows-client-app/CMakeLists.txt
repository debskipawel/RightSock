add_executable(windows-client-app)

target_sources(windows-client-app PRIVATE main.cpp)

target_link_libraries(windows-client-app PUBLIC socket-library)

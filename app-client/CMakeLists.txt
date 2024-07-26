add_executable(app-client)

target_sources(app-client PRIVATE main.cpp)

target_link_libraries(app-client PUBLIC socket-library)

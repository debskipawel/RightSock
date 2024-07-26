project(socket-library)

add_library(socket-library STATIC)

target_include_directories(
  socket-library PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)

set(SOCKET_LIBRARY_INCLUDE
    "include/Core/IReceivable.hpp"
    "include/Core/ISendable.hpp"
    "include/Core/Socket.hpp"
    "include/Core/SocketPayload.hpp"
    "include/Core/Types.hpp"
    "include/TCP/SocketTCP.hpp"
    "include/TCP/ClientSocketTCP.hpp"
    "include/TCP/ServerSocketTCP.hpp"
    "include/TCP/ListeningSocketTCP.hpp"
    "include/UDP/SocketUDP.hpp")

set(SOCKET_LIBRARY_COMPILE)

set(SOCKET_LIBRARY_WINDOWS_INCLUDE)

set(SOCKET_LIBRARY_WINDOWS_COMPILE
    "src/Core/Windows/Socket.cpp" "src/TCP/Windows/SocketTCP.cpp"
    "src/TCP/Windows/ClientSocketTCP.cpp" "src/TCP/Windows/ServerSocketTCP.cpp"
    "src/TCP/Windows/ListeningSocketTCP.cpp" "src/UDP/Windows/SocketUDP.cpp")

set(SOCKET_LIBRARY_OTHER_INCLUDE)

set(SOCKET_LIBRARY_OTHER_COMPILE
    "src/Core/Other/Socket.cpp" "src/TCP/Other/SocketTCP.cpp"
    "src/TCP/Other/ClientSocketTCP.cpp" "src/TCP/Other/ServerSocketTCP.cpp"
    "src/TCP/Other/ListeningSocketTCP.cpp" "src/UDP/Other/SocketUDP.cpp")

target_sources(socket-library PRIVATE ${SOCKET_LIBRARY_INCLUDE}
                                      ${SOCKET_LIBRARY_COMPILE})

if(WIN32)

  target_sources(socket-library PRIVATE ${SOCKET_LIBRARY_WINDOWS_INCLUDE}
                                        ${SOCKET_LIBRARY_WINDOWS_COMPILE})

else()

  target_sources(socket-library PRIVATE ${SOCKET_LIBRARY_OTHER_INCLUDE}
                                        ${SOCKET_LIBRARY_OTHER_COMPILE})

endif()

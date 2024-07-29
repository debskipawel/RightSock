project(right-sock)

add_library(right-sock STATIC)

target_include_directories(
  right-sock PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)

set(RIGHT_SOCK_INCLUDE
    "include/RightSockContext.hpp"
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

set(RIGHT_SOCK_COMPILE "src/RightSockContext.cpp")

set(RIGHT_SOCK_WINDOWS_INCLUDE)

set(RIGHT_SOCK_WINDOWS_COMPILE
    "src/Core/Windows/Socket.cpp" "src/TCP/Windows/SocketTCP.cpp"
    "src/TCP/Windows/ClientSocketTCP.cpp" "src/TCP/Windows/ServerSocketTCP.cpp"
    "src/TCP/Windows/ListeningSocketTCP.cpp" "src/UDP/Windows/SocketUDP.cpp")

set(RIGHT_SOCK_OTHER_INCLUDE)

set(RIGHT_SOCK_OTHER_COMPILE
    "src/Core/Other/Socket.cpp" "src/TCP/Other/SocketTCP.cpp"
    "src/TCP/Other/ClientSocketTCP.cpp" "src/TCP/Other/ServerSocketTCP.cpp"
    "src/TCP/Other/ListeningSocketTCP.cpp" "src/UDP/Other/SocketUDP.cpp")

target_sources(right-sock PRIVATE ${RIGHT_SOCK_INCLUDE} ${RIGHT_SOCK_COMPILE})

if(WIN32)

  target_sources(right-sock PRIVATE ${RIGHT_SOCK_WINDOWS_INCLUDE}
                                    ${RIGHT_SOCK_WINDOWS_COMPILE})

else()

  target_sources(right-sock PRIVATE ${RIGHT_SOCK_OTHER_INCLUDE}
                                    ${RIGHT_SOCK_OTHER_COMPILE})

endif()

project(socket-library)

add_library(socket-library STATIC)

target_include_directories(
  socket-library PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src)

set(SOCKET_LIBRARY_INCLUDE
    "src/Core/IReceivable.hpp"
    "src/Core/ISendable.hpp"
    "src/Core/Socket.hpp"
    "src/Core/SocketPayload.hpp"
    "src/Core/Types.hpp"
    "src/TCP/ActiveSocketTCP.hpp"
    "src/TCP/ClientSocketTCP.hpp"
    "src/TCP/ServerSocketTCP.hpp"
    "src/TCP/ListeningSocketTCP.hpp")

set(SOCKET_LIBRARY_COMPILE)

set(SOCKET_LIBRARY_WINDOWS_INCLUDE)

set(SOCKET_LIBRARY_WINDOWS_COMPILE
    "src/Core/Windows/Socket.cpp" "src/TCP/Windows/ActiveSocketTCP.cpp"
    "src/TCP/Windows/ClientSocketTCP.cpp" "src/TCP/Windows/ServerSocketTCP.cpp"
    "src/TCP/Windows/ListeningSocketTCP.cpp")

set(SOCKET_LIBRARY_OTHER_INCLUDE)

set(SOCKET_LIBRARY_OTHER_COMPILE
    "src/Core/Other/Socket.cpp"
)

target_sources(socket-library PRIVATE ${SOCKET_LIBRARY_INCLUDE}
                                      ${SOCKET_LIBRARY_COMPILE})

if(WIN32)

  target_sources(socket-library PRIVATE ${SOCKET_LIBRARY_WINDOWS_INCLUDE}
                                        ${SOCKET_LIBRARY_WINDOWS_COMPILE})

else()

  target_sources(socket-library PRIVATE ${SOCKET_LIBRARY_OTHER_INCLUDE}
                                        ${SOCKET_LIBRARY_OTHER_COMPILE})

endif()

#include <TCP/ServerSocketTCP.hpp>

namespace RightSock
{

ServerSocketTCP::ServerSocketTCP(int socket, const Address& address, Port port)
    : SocketTCP(socket, address, port)
{
}

} // namespace RightSock

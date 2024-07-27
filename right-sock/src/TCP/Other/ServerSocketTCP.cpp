#include <TCP/ServerSocketTCP.hpp>

namespace Sock
{

ServerSocketTCP::ServerSocketTCP(int socket, const std::string& address, port_t port)
    : ActiveSocketTCP(socket, address, port)
{
}

} // namespace Sock

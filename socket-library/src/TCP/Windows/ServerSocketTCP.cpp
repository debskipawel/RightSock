#include <TCP/ServerSocketTCP.hpp>

namespace Sock
{

ServerSocketTCP::ServerSocketTCP(int socket, const std::string& address, port_t port)
    : ActiveSocketTCP(socket, address, port)
{
}

auto ServerSocketTCP::IsValid() const noexcept -> bool
{
    return false;
}

} // namespace Sock

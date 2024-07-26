#include <Core/Socket.hpp>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace Sock
{

Socket::Socket()
    : Socket(-1, "", 0)
{
}

Socket::Socket(int socket, const std::string& address, port_t port)
    : m_Socket(socket), m_Address(address), m_Port(port)
{
}

Socket::~Socket() noexcept
{
    CloseConnection();
}

auto Socket::InitializeSystem() -> bool
{
    return true;
}

auto Socket::ShutdownSystem() -> void
{
}

auto Socket::IsValid() const noexcept -> bool
{
    return (m_Socket >= 0);
}

auto Socket::CloseConnection() -> void
{
    close(m_Socket);
    m_Socket = -1;
    m_Address = "";
    m_Port = 0;
}

} // namespace Sock
#include <Core/Socket.hpp>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace Sock
{

Socket::Socket()
    : Socket(INVALID_SOCKET, "", 0)
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
    WSADATA wsaData;
    int initializeResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    return (initializeResult == 0);
}

auto Socket::ShutdownSystem() -> void
{
    WSACleanup();
}

auto Socket::IsValid() const noexcept -> bool
{
    return (m_Socket != INVALID_SOCKET);
}

auto Socket::CloseConnection() -> void
{
    closesocket(m_Socket);
}

} // namespace Sock
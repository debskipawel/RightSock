#include <Core/Socket.hpp>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace Sock
{

Socket::Socket(std::string address, port_t port)
    : m_Address(address), m_Port(port)
{
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* result = {};

    auto portStr = std::to_string(m_Port);

    auto iResult = getaddrinfo(m_Address.c_str(), portStr.c_str(), &hints, &result);

    if (iResult != 0)
    {
        m_Socket = INVALID_SOCKET;
        m_Address = {};
        m_Port = {};

        return;
    }

    m_Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (m_Socket == INVALID_SOCKET)
    {
        m_Address = {};
        m_Port = {};

        return;
    }

    iResult = bind(m_Socket, result->ai_addr, (int) result->ai_addrlen);

    if (iResult == SOCKET_ERROR)
    {
        closesocket(m_Socket);

        m_Socket = INVALID_SOCKET;
        m_Address = {};
        m_Port = {};

        return;
    }
}

Socket::Socket(int socket, std::string address, port_t port)
    : m_Socket(socket), m_Address(address), m_Port(port)
{
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
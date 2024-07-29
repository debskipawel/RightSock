#include <Core/Socket.hpp>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace RightSock
{

static bool s_Initialized = false;

Socket::Socket()
    : Socket(INVALID_SOCKET, "", 0)
{
}

Socket::Socket(int socket, const Address& address, Port port)
    : m_Socket(socket), m_Address(address), m_Port(port)
{
}

Socket::~Socket() noexcept
{
    CloseConnection();
}

auto Socket::InitializeSystem() -> bool
{
    if (s_Initialized)
    {
        return true;
    }

    WSADATA wsaData;
    int initializeResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    s_Initialized = (initializeResult == 0);

    return s_Initialized;
}

auto Socket::ShutdownSystem() -> void
{
    if (!s_Initialized)
    {
        return;
    }

    s_Initialized = false;

    WSACleanup();
}

auto Socket::IsValid() const noexcept -> bool
{
    return (m_Socket != INVALID_SOCKET);
}

auto Socket::CloseConnection() -> void
{
    closesocket(m_Socket);
    m_Socket = INVALID_SOCKET;
    m_Address = "";
    m_Port = 0;
}

} // namespace RightSock
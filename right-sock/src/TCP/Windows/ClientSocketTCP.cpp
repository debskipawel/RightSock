#include <TCP/ClientSocketTCP.hpp>

#include <array>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace Sock
{

ClientSocketTCP::ClientSocketTCP(const std::string& serverAddress, port_t serverPort)
    : m_Connected(false)
{
    addrinfo hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    auto serverPortStr = std::to_string(serverPort);

    addrinfo* result = nullptr;

    if (getaddrinfo(serverAddress.c_str(), serverPortStr.c_str(), &hints, &result) != 0)
    {
        m_Socket = INVALID_SOCKET;
        return;
    }

    for (auto ptr = result; ptr != nullptr; ptr = ptr->ai_next)
    {
        auto serverSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (serverSocket == INVALID_SOCKET)
        {
            m_Socket = INVALID_SOCKET;
            return;
        }

        if (connect(serverSocket, ptr->ai_addr, (int) ptr->ai_addrlen) == SOCKET_ERROR)
        {
            auto error = WSAGetLastError();

            closesocket(serverSocket);
            continue;
        }

        m_Connected = true;

        m_Socket = serverSocket;
        m_Address = serverAddress;
        m_Port = serverPort;

        break;
    }

    freeaddrinfo(result);
}

auto ClientSocketTCP::IsValid() const noexcept -> bool
{
    return Socket::IsValid() && m_Connected;
}

} // namespace Sock

#include <TCP/ListeningSocketTCP.hpp>

#include <array>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace Sock
{

ListeningSocketTCP::ListeningSocketTCP(const std::string& address, port_t port)
    : m_Listening(false)
{
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    addrinfo* result = {};

    auto portStr = std::to_string(port);

    auto iResult = getaddrinfo(address.c_str(), portStr.c_str(), &hints, &result);

    if (iResult != 0)
    {
        return;
    }

    m_Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (m_Socket == INVALID_SOCKET)
    {
        return;
    }

    iResult = bind(m_Socket, result->ai_addr, (int) result->ai_addrlen);

    freeaddrinfo(result);

    if (iResult == SOCKET_ERROR)
    {
        CloseConnection();

        return;
    }

    iResult = listen(m_Socket, SOMAXCONN);

    if (iResult == SOCKET_ERROR)
    {
        CloseConnection();

        return;
    }

    m_Listening = true;
    m_Address = address;
    m_Port = port;
}

auto ListeningSocketTCP::WaitForConnection() -> std::shared_ptr<ServerSocketTCP>
{
    if (!IsValid())
    {
        return nullptr;
    }

    sockaddr_in clientInfo = {};
    int clientInfoSize = sizeof(clientInfo);

    auto clientSocket = accept(m_Socket, (sockaddr*) (&clientInfo), &clientInfoSize);

    if (clientSocket == INVALID_SOCKET)
    {
        return {};
    };

    std::array<char, 50> address;

    auto ip = inet_ntop(clientInfo.sin_family, &clientInfo.sin_addr, address.data(), address.size());
    auto port = ntohs(clientInfo.sin_port);

    return std::make_shared<ServerSocketTCP>(static_cast<int>(clientSocket), std::string(ip), port);
}

auto ListeningSocketTCP::IsValid() const noexcept -> bool
{
    return Socket::IsValid() && m_Listening;
}

} // namespace Sock
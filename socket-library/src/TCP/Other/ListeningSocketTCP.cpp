#include <TCP/ListeningSocketTCP.hpp>

#include <array>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace Sock
{

ListeningSocketTCP::ListeningSocketTCP(const std::string& address, port_t port)
    : m_Listening(false)
{
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_Socket < 0)
    {
        return;
    }

    sockaddr_in serverAddress = {};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, address.c_str(), &serverAddress.sin_addr) <= 0)
    {
        CloseConnection();
        return;
    }

    if (bind(m_Socket, (sockaddr*) (&serverAddress), sizeof(serverAddress)) < 0)
    {
        CloseConnection();
        return;
    }

    if (listen(m_Socket, SOMAXCONN) < 0)
    {
        CloseConnection();
        return;
    }

    m_Listening = true;
    m_Address = address;
    m_Port = port;
}

auto ListeningSocketTCP::WaitForConnection() -> std::unique_ptr<ServerSocketTCP>
{
    if (!IsValid())
    {
        return nullptr;
    }

    sockaddr_in clientInfo = {};
    socklen_t clientInfoSize = sizeof(clientInfo);

    auto clientSocket = accept(m_Socket, (sockaddr*) (&clientInfo), &clientInfoSize);

    if (clientSocket < 0)
    {
        return {};
    };

    const char* ip = inet_ntoa(clientInfo.sin_addr);

    auto address = std::string(ip);
    auto port = ntohs(clientInfo.sin_port);

    return std::make_unique<ServerSocketTCP>(static_cast<int>(clientSocket), address, port);
}

auto ListeningSocketTCP::IsValid() const noexcept -> bool
{
    return Socket::IsValid() && m_Listening;
}

} // namespace Sock
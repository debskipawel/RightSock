#include <TCP/ListeningSocketTCP.hpp>

#include <array>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace RightSock
{

ListeningSocketTCP::ListeningSocketTCP(const Address& address, Port port)
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

auto ListeningSocketTCP::WaitForConnection() -> std::shared_ptr<ServerSocketTCP>
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

    auto ip = inet_ntoa(clientInfo.sin_addr);
    auto port = ntohs(clientInfo.sin_port);

    return std::shared_ptr<ServerSocketTCP>(new ServerSocketTCP {static_cast<int>(clientSocket), std::string(ip), port});
}

auto ListeningSocketTCP::IsValid() const noexcept -> bool
{
    return Socket::IsValid() && m_Listening;
}

} // namespace RightSock
#include <TCP/ClientSocketTCP.hpp>

#include <array>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace Sock
{

ClientSocketTCP::ClientSocketTCP(const std::string& serverAddress, port_t serverPort)
    : m_Connected(false)
{
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_Socket < 0)
    {
        return;
    }

    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverAddress.c_str(), &address.sin_addr) <= 0)
    {
        CloseConnection();

        return;
    }

    auto connectResult = connect(m_Socket, (sockaddr*) (&address), sizeof(address));

    if (connectResult < 0)
    {
        CloseConnection();

        return;
    }

    m_Address = serverAddress;
    m_Port = serverPort;
    m_Connected = true;
}

auto ClientSocketTCP::IsValid() const noexcept -> bool
{
    return Socket::IsValid() && m_Connected;
}

} // namespace Sock

#include <TCP/ActiveSocketTCP.hpp>

#include <array>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace Sock
{

ActiveSocketTCP::ActiveSocketTCP()
    : Socket()
{
}

ActiveSocketTCP::ActiveSocketTCP(int socket, const std::string& address, port_t port)
    : Socket(socket, address, port)
{
}

auto ActiveSocketTCP::Receive() const -> SocketPayload
{
    std::array<char, 512> recvBuffer;

    int bytesReceived = recv(m_Socket, recvBuffer.data(), recvBuffer.size(), 0);

    if (bytesReceived < 0)
    {
        return SocketPayload("", m_Address, m_Port);
    }

    std::string message(recvBuffer.begin(), recvBuffer.begin() + bytesReceived);

    return SocketPayload(message, m_Address, m_Port);
}

auto ActiveSocketTCP::Send(const SocketPayload& payload) const -> void
{
    if (payload.m_Address != m_Address || payload.m_Port != m_Port)
    {
        return;
    }

    const auto& message = payload.m_Message;

    auto bytesSent = send(m_Socket, message.c_str(), message.length(), 0);
}

} // namespace Sock

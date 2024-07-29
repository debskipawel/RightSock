#include <TCP/SocketTCP.hpp>

#include <array>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace RightSock
{

SocketTCP::SocketTCP()
    : Socket()
{
}

SocketTCP::SocketTCP(int socket, const Address& address, Port port)
    : Socket(socket, address, port)
{
}

auto SocketTCP::Receive() const -> SocketPayload
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

auto SocketTCP::Send(const SocketPayload& payload) const -> SendStatus
{
    if (payload.m_Address != m_Address || payload.m_Port != m_Port)
    {
        return;
    }

    const auto& message = payload.m_Message;

    auto bytesSent = send(m_Socket, message.c_str(), message.length(), 0);

    if (bytesSent == 0)
    {
        return SendStatus::CONNECTION_CLOSED;
    }

    return SendStatus::SENT;
}

} // namespace RightSock

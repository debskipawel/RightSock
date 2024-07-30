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

auto SocketTCP::Receive() const -> ReceiveResult
{
    std::array<char, 512> recvBuffer;

    int bytesReceived = recv(m_Socket, recvBuffer.data(), recvBuffer.size(), 0);

    if (bytesReceived == 0)
    {
        return {ReceiveStatusCode::CONNECTION_CLOSED, SocketPayload::DEFAULT()};
    }
    else if (bytesReceived < 0)
    {
        return {ReceiveStatusCode::RECV_ERROR, SocketPayload::DEFAULT()};
    }

    std::string message(recvBuffer.begin(), recvBuffer.begin() + bytesReceived);

    return {ReceiveStatusCode::RECEIVED, SocketPayload(message, m_Address, m_Port)};
}

auto SocketTCP::Send(const SocketPayload& payload) const -> SendStatusCode
{
    if (payload.m_Address != m_Address || payload.m_Port != m_Port)
    {
        return SendStatusCode::VALIDATION_ERROR;
    }

    const auto& message = payload.m_Message;

    auto bytesSent = send(m_Socket, message.c_str(), message.length(), 0);

    if (bytesSent == 0)
    {
        return SendStatusCode::CONNECTION_CLOSED;
    }

    return SendStatusCode::SENT;
}

} // namespace RightSock

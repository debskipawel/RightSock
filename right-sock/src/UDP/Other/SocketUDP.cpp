#include <UDP/SocketUDP.hpp>

#include <array>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace RightSock
{

SocketUDP::SocketUDP(const Address& address, Port port)
{
    m_Socket = socket(AF_INET, SOCK_DGRAM, 0);

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

    m_Address = address;
    m_Port = port;
}

auto SocketUDP::Receive() const -> ReceiveResult
{
    std::array<char, 512> recvBuffer;

    sockaddr_in sender = {};
    int senderSize = sizeof(sender);

    int receiveResult = recvfrom(m_Socket, recvBuffer.data(), recvBuffer.size(), 0, (sockaddr*) (&sender), &senderSize);

    if (receiveResult < 0)
    {
        return {ReceiveStatusCode::RECV_ERROR, SocketPayload("", "", 0)};
    }

    auto message = std::string(recvBuffer.data(), recvBuffer.data() + receiveResult);

    auto ip = inet_ntoa(sender.sin_addr);
    auto port = ntohs(sender.sin_port);

    return {ReceiveStatusCode::RECEIVED, SocketPayload(message, std::string(ip), port)};
}

auto SocketUDP::Send(const SocketPayload& payload) const -> SendStatusCode
{
    sockaddr_in dest = {};
    dest.sin_family = AF_INET;
    dest.sin_port = htons(payload.m_Port);
    inet_pton(AF_INET, payload.m_Address.c_str(), &dest.sin_addr);

    int sendResult = sendto(m_Socket, payload.m_Message.data(), payload.m_Message.length(), 0, (sockaddr*) (&dest), sizeof(dest));

    if (sendResult == 0)
    {
        return SendStatusCode::CONNECTION_CLOSED;
    }
    else if (sendResult < 0)
    {
        return SendStatusCode::SEND_ERROR;
    }

    return SendStatusCode::SENT;
}

} // namespace RightSock

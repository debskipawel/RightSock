#include <UDP/SocketUDP.hpp>

#include <array>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace RightSock
{

SocketUDP::SocketUDP(const Address& address, Port port)
{
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
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

    m_Address = address;
    m_Port = port;
}

auto SocketUDP::Receive() const -> ReceiveResult
{
    std::array<char, 512> recvBuffer;

    sockaddr_in sender = {};
    int senderSize = sizeof(sender);

    int receiveResult = recvfrom(m_Socket, recvBuffer.data(), recvBuffer.size(), 0, (sockaddr*) (&sender), &senderSize);

    if (receiveResult == SOCKET_ERROR)
    {
        return {ReceiveStatusCode::RECV_ERROR, SocketPayload::DEFAULT()};
    }

    auto message = std::string(recvBuffer.data(), recvBuffer.data() + receiveResult);

    std::array<char, 50> address;

    auto ip = inet_ntop(sender.sin_family, &sender.sin_addr, address.data(), address.size());
    auto port = ntohs(sender.sin_port);

    return {ReceiveStatusCode::RECEIVED, SocketPayload(message, std::string(ip), port)};
}

auto SocketUDP::Send(const SocketPayload& payload) const -> SendStatusCode
{
    sockaddr_in dest = {};
    dest.sin_family = AF_INET;
    dest.sin_port = htons(payload.m_Port);
    inet_pton(AF_INET, payload.m_Address.c_str(), &dest.sin_addr.s_addr);

    int sendResult = sendto(m_Socket, payload.m_Message.data(), payload.m_Message.length(), 0, (sockaddr*) (&dest), sizeof(dest));

    if (sendResult == 0)
    {
        return SendStatusCode::CONNECTION_CLOSED;
    }

    return SendStatusCode::SENT;
}

} // namespace RightSock

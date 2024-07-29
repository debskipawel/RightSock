#pragma once

#include <string>

#include <Core/Types.hpp>

namespace RightSock
{

struct SocketPayload
{
    SocketPayload(const std::string& message, const std::string& address, Port port)
        : m_Message(message), m_Address(address), m_Port(port) { }

    std::string m_Message;
    Address m_Address;
    Port m_Port;
};

} // namespace RightSock

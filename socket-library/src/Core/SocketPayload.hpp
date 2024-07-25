#pragma once

#include <string>

#include <Core/Types.hpp>

namespace Sock
{

struct SocketPayload
{
    SocketPayload(const std::string& message, const std::string& address, port_t port)
        : m_Message(message), m_Address(address), m_Port(port) { }

    std::string m_Message;
    std::string m_Address;
    port_t m_Port;
};

} // namespace Sock

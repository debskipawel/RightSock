#pragma once

#include <Core/IReceivable.hpp>
#include <Core/ISendable.hpp>
#include <Core/Socket.hpp>

namespace Sock
{

class SocketUDP : public Socket, public IReceivable, public ISendable
{
public:
    SocketUDP(const std::string& address, port_t port);
    virtual ~SocketUDP() = default;

    virtual auto Receive() const -> SocketPayload override;
    virtual auto Send(const SocketPayload& payload) const -> void override;
};

} // namespace Sock

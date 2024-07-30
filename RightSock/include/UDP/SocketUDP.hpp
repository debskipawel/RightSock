#pragma once

#include <Core/IReceivable.hpp>
#include <Core/ISendable.hpp>
#include <Core/Socket.hpp>

namespace RightSock
{

class SocketUDP : public Socket, public IReceivable, public ISendable
{
public:
    virtual ~SocketUDP() = default;

    virtual auto Receive() const -> ReceiveResult override;
    virtual auto Send(const SocketPayload& payload) const -> SendStatusCode override;

protected:
    SocketUDP(const Address& address, Port port);

protected:
    friend class Context;
};

} // namespace RightSock

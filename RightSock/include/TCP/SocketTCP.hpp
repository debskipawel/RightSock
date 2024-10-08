#pragma once

#include <Core/IReceivable.hpp>
#include <Core/ISendable.hpp>
#include <Core/Socket.hpp>

namespace RightSock
{

class SocketTCP : public Socket, public IReceivable, public ISendable
{
public:
    virtual auto Receive() const -> ReceiveResult override;
    virtual auto Send(const SocketPayload& payload) const -> SendStatusCode override;

protected:
    SocketTCP();
    SocketTCP(int socket, const Address& address, Port port);
    virtual ~SocketTCP() noexcept = default;
};

} // namespace RightSock

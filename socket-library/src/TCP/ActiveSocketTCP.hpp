#pragma once

#include <Core/IReceivable.hpp>
#include <Core/ISendable.hpp>
#include <Core/Socket.hpp>

namespace Sock
{

class ActiveSocketTCP : public Socket, public IReceivable, public ISendable
{
public:
    ActiveSocketTCP();
    ActiveSocketTCP(int socket, const std::string& address, port_t port);
    virtual ~ActiveSocketTCP() noexcept = default;

    virtual auto Receive() const -> SocketPayload override;
    virtual auto Send(const SocketPayload& payload) const -> void override;
};

} // namespace Sock

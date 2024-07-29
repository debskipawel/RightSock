#pragma once

#include <Core/IReceivable.hpp>
#include <Core/ISendable.hpp>
#include <Core/Socket.hpp>

namespace Sock
{

class SocketTCP : public Socket, public IReceivable, public ISendable
{
public:
    virtual auto Address() const noexcept -> std::string
    {
        return m_Address;
    }

    virtual auto Port() const noexcept -> port_t
    {
        return m_Port;
    }

    virtual auto Receive() const -> SocketPayload override;
    virtual auto Send(const SocketPayload& payload) const -> SendStatus override;

protected:
    SocketTCP();
    SocketTCP(int socket, const std::string& address, port_t port);
    virtual ~SocketTCP() noexcept = default;
};

} // namespace Sock

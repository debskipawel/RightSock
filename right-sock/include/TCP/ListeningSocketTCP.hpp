#pragma once

#include <memory>

#include <Core/Socket.hpp>
#include <TCP/ServerSocketTCP.hpp>

namespace Sock
{

class ListeningSocketTCP : public Socket
{
public:
    ListeningSocketTCP(const std::string& address, port_t port);
    virtual ~ListeningSocketTCP() noexcept = default;

    virtual auto WaitForConnection() -> std::shared_ptr<ServerSocketTCP>;

    virtual auto IsValid() const noexcept -> bool override;

protected:
    bool m_Listening;
};

} // namespace Sock

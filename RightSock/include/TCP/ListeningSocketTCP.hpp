#pragma once

#include <memory>

#include <Core/Socket.hpp>
#include <TCP/ServerSocketTCP.hpp>

namespace RightSock
{

class ListeningSocketTCP : public Socket
{
public:
    virtual ~ListeningSocketTCP() noexcept = default;

    virtual auto WaitForConnection() -> std::shared_ptr<ServerSocketTCP>;

    virtual auto IsValid() const noexcept -> bool override;

protected:
    ListeningSocketTCP(const Address& address, Port port);

    bool m_Listening;

protected:
    friend class Context;
};

} // namespace RightSock

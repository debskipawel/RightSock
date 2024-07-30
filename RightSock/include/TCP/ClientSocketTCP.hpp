#pragma once

#include <TCP/SocketTCP.hpp>

namespace RightSock
{

class ClientSocketTCP : public SocketTCP
{
public:
    virtual ~ClientSocketTCP() noexcept = default;

    virtual auto IsValid() const noexcept -> bool override;

protected:
    ClientSocketTCP(const Address& serverAddress, Port serverPort);

    bool m_Connected;

protected:
    friend class Context;
};

} // namespace RightSock

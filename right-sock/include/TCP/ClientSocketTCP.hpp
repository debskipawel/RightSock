#pragma once

#include <TCP/SocketTCP.hpp>

namespace Sock
{

class ClientSocketTCP : public SocketTCP
{
public:
    virtual ~ClientSocketTCP() noexcept = default;

    virtual auto IsValid() const noexcept -> bool override;

protected:
    ClientSocketTCP(const std::string& serverAddress, port_t serverPort);

    bool m_Connected;

protected:
    friend class RightSockContext;
};

} // namespace Sock

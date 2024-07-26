#pragma once

#include <TCP/SocketTCP.hpp>

namespace Sock
{

class ClientSocketTCP : public SocketTCP
{
public:
    ClientSocketTCP(const std::string& serverAddress, port_t serverPort);
    virtual ~ClientSocketTCP() noexcept = default;

    virtual auto IsValid() const noexcept -> bool override;

protected:
    bool m_Connected;
};

} // namespace Sock

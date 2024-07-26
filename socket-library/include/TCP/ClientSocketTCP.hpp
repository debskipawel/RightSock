#pragma once

#include <TCP/ActiveSocketTCP.hpp>

namespace Sock
{

class ClientSocketTCP : public ActiveSocketTCP
{
public:
    ClientSocketTCP(const std::string& serverAddress, port_t serverPort);
    virtual ~ClientSocketTCP() noexcept = default;

    virtual auto IsValid() const noexcept -> bool override;

protected:
    bool m_Connected;
};

} // namespace Sock

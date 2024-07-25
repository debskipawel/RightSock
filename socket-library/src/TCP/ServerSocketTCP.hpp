#pragma once

#include <TCP/ActiveSocketTCP.hpp>

namespace Sock
{

class ServerSocketTCP : public ActiveSocketTCP
{
public:
    ServerSocketTCP(int socket, const std::string& address, port_t port);
    virtual ~ServerSocketTCP() noexcept = default;

    virtual auto IsValid() const noexcept -> bool override;
};

} // namespace Sock

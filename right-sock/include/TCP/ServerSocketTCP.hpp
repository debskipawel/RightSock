#pragma once

#include <TCP/SocketTCP.hpp>

namespace Sock
{

class ServerSocketTCP : public SocketTCP
{
public:
    ServerSocketTCP(int socket, const std::string& address, port_t port);
    virtual ~ServerSocketTCP() noexcept = default;
};

} // namespace Sock

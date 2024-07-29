#pragma once

#include <TCP/SocketTCP.hpp>

namespace Sock
{

class ServerSocketTCP : public SocketTCP
{
public:
    virtual ~ServerSocketTCP() noexcept = default;

protected:
    ServerSocketTCP(int socket, const std::string& address, port_t port);

protected:
    friend class ListeningSocketTCP;
    friend class RightSockContext;
};

} // namespace Sock

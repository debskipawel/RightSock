#pragma once

#include <TCP/SocketTCP.hpp>

namespace RightSock
{

class ServerSocketTCP : public SocketTCP
{
public:
    virtual ~ServerSocketTCP() noexcept = default;

protected:
    ServerSocketTCP(int socket, const Address& address, Port port);

protected:
    friend class ListeningSocketTCP;
    friend class Context;
};

} // namespace RightSock

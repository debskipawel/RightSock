#pragma once

#include <string>

namespace Sock
{

typedef unsigned short port_t;

class Socket
{
public:
    Socket(std::string address, port_t port);
    Socket(int socket, std::string address, port_t port);

    static auto InitializeSystem() -> bool;
    static auto ShutdownSystem() -> void;

    virtual auto IsValid() const noexcept -> bool;

    virtual auto CloseConnection() -> void;

protected:
    std::string m_Address;
    port_t m_Port;

    int m_Socket;
};

} // namespace Sock

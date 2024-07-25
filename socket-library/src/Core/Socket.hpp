#pragma once

#include <string>

#include <Core/Types.hpp>

namespace Sock
{

class Socket
{
public:
    Socket();
    Socket(int socket, const std::string& address, port_t port);
    virtual ~Socket() noexcept;

    Socket(const Socket& other) = delete;
    auto operator=(const Socket& other) -> Socket = delete;

    static auto InitializeSystem() -> bool;
    static auto ShutdownSystem() -> void;

    virtual auto IsValid() const noexcept -> bool;

    virtual auto CloseConnection() -> void final;

protected:
    std::string m_Address;
    port_t m_Port;

    int m_Socket;
};

} // namespace Sock

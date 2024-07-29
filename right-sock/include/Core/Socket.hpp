#pragma once

#include <string>

#include <Core/Types.hpp>

namespace Sock
{

class Socket
{
public:
    virtual ~Socket() noexcept;

    static auto InitializeSystem() -> bool;
    static auto ShutdownSystem() -> void;

    inline virtual auto Id() const noexcept -> int
    {
        return m_Socket;
    }

    virtual auto IsValid() const noexcept -> bool;

    virtual auto CloseConnection() -> void final;

protected:
    std::string m_Address;
    port_t m_Port;

    unsigned long m_Socket;

protected:
    Socket();
    Socket(int socket, const std::string& address, port_t port);

    Socket(const Socket& other) = delete;
    auto operator=(const Socket& other) -> Socket = delete;
};

} // namespace Sock

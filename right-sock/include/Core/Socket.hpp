#pragma once

#include <string>

#include <Core/Types.hpp>

namespace RightSock
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

    virtual auto GetAddress() const noexcept -> std::string
    {
        return m_Address;
    }

    virtual auto GetPort() const noexcept -> Port
    {
        return m_Port;
    }

    virtual auto IsValid() const noexcept -> bool;

    virtual auto CloseConnection() -> void final;

protected:
    Address m_Address;
    Port m_Port;

    int m_Socket;

protected:
    Socket();
    Socket(int socket, const Address& address, Port port);

    Socket(const Socket& other) = delete;
    auto operator=(const Socket& other) -> Socket = delete;
};

} // namespace RightSock

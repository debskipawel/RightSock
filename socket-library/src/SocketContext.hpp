#pragma once

#include <memory>

#include <TCP/ClientSocketTCP.hpp>
#include <TCP/ListeningSocketTCP.hpp>

namespace Sock
{

class SocketContext
{
public:
    auto CreateServerTCP(const std::string& address, port_t port) -> std::shared_ptr<ListeningSocketTCP>;
    auto ConnectToServerTCP(const std::string& serverAddress, port_t serverPort) -> std::shared_ptr<ClientSocketTCP>;

public:
    inline static auto GetInstance() noexcept -> SocketContext&
    {
        return s_Instance;
    }

protected:
    SocketContext();
    ~SocketContext();

    static SocketContext s_Instance;

private:
    SocketContext(const SocketContext& other) = delete;
    auto operator=(const SocketContext& other) = delete;

    friend class Socket;
};

} // namespace Sock

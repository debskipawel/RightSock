#pragma once

#include <TCP/ClientSocketTCP.hpp>
#include <TCP/ListeningSocketTCP.hpp>
#include <UDP/SocketUDP.hpp>

namespace Sock
{

class RightSockContext
{
public:
    ~RightSockContext() noexcept;

    auto StartServerTCP(const std::string& address, port_t port) -> std::shared_ptr<ListeningSocketTCP>;
    auto ConnectToServerTCP(const std::string& address, port_t port) -> std::shared_ptr<ClientSocketTCP>;

    auto CreateConnectionPointUDP(const std::string& address, port_t port) -> std::shared_ptr<SocketUDP>;

    static auto Instance() -> RightSockContext&;

private:
    RightSockContext() noexcept;

    static std::unique_ptr<RightSockContext> s_Instance;

private:
    RightSockContext(const RightSockContext& other) = delete;
    RightSockContext(RightSockContext&& other) = delete;
    auto operator=(const RightSockContext& other) -> RightSockContext& = delete;
    auto operator=(RightSockContext&& other) -> RightSockContext& = delete;
};

} // namespace Sock

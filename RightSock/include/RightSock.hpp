#pragma once

#include <TCP/ClientSocketTCP.hpp>
#include <TCP/ListeningSocketTCP.hpp>
#include <UDP/SocketUDP.hpp>

namespace RightSock
{

class Context
{
public:
    ~Context() noexcept;

    auto StartServerTCP(const Address& address, Port port) -> std::shared_ptr<ListeningSocketTCP>;
    auto ConnectToServerTCP(const Address& address, Port port) -> std::shared_ptr<ClientSocketTCP>;

    auto CreateConnectionPointUDP(const Address& address, Port port) -> std::shared_ptr<SocketUDP>;

    static auto Instance() -> Context&;

private:
    Context() noexcept;

    static std::unique_ptr<Context> s_Instance;

private:
    Context(const Context& other) = delete;
    Context(Context&& other) = delete;
    auto operator=(const Context& other) -> Context& = delete;
    auto operator=(Context&& other) -> Context& = delete;
};

} // namespace RightSock

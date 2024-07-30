#include "RightSock.hpp"

namespace RightSock
{

std::unique_ptr<Context> Context::s_Instance = {};

auto Context::StartServerTCP(const std::string& address, Port port) -> std::shared_ptr<ListeningSocketTCP>
{
    return std::shared_ptr<ListeningSocketTCP>(new ListeningSocketTCP {address, port});
}

auto Context::ConnectToServerTCP(const std::string& address, Port port) -> std::shared_ptr<ClientSocketTCP>
{
    return std::shared_ptr<ClientSocketTCP>(new ClientSocketTCP {address, port});
}

auto Context::CreateConnectionPointUDP(const std::string& address, Port port) -> std::shared_ptr<SocketUDP>
{
    return std::shared_ptr<SocketUDP>(new SocketUDP {address, port});
}

auto Context::Instance() -> Context&
{
    if (!s_Instance)
    {
        s_Instance = std::unique_ptr<Context>(new Context);
    }

    return *s_Instance;
}

Context::Context() noexcept
{
    Socket::InitializeSystem();
}

Context::~Context() noexcept
{
    Socket::ShutdownSystem();
}

} // namespace RightSock

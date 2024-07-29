#include "RightSockContext.hpp"

namespace Sock
{

std::unique_ptr<RightSockContext> RightSockContext::s_Instance = {};

auto RightSockContext::StartServerTCP(const std::string& address, port_t port) -> std::shared_ptr<ListeningSocketTCP>
{
    return std::shared_ptr<ListeningSocketTCP>(new ListeningSocketTCP {address, port});
}

auto RightSockContext::ConnectToServerTCP(const std::string& address, port_t port) -> std::shared_ptr<ClientSocketTCP>
{
    return std::shared_ptr<ClientSocketTCP>(new ClientSocketTCP {address, port});
}

auto RightSockContext::CreateConnectionPointUDP(const std::string& address, port_t port) -> std::shared_ptr<SocketUDP>
{
    return std::shared_ptr<SocketUDP>(new SocketUDP {address, port});
}

auto RightSockContext::Instance() -> RightSockContext&
{
    if (!s_Instance)
    {
        s_Instance = std::unique_ptr<RightSockContext>(new RightSockContext);
    }

    return *s_Instance;
}

RightSockContext::RightSockContext() noexcept
{
    Socket::InitializeSystem();
}

RightSockContext::~RightSockContext() noexcept
{
    Socket::ShutdownSystem();
}

} // namespace Sock

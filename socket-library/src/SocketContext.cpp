#include <SocketContext.hpp>

namespace Sock
{

SocketContext SocketContext::s_Instance = {};

auto SocketContext::CreateServerTCP(const std::string& address, port_t port) -> std::shared_ptr<ListeningSocketTCP>
{
    return std::make_shared<ListeningSocketTCP>(address, port);
}

auto SocketContext::ConnectToServerTCP(const std::string& serverAddress, port_t serverPort) -> std::shared_ptr<ClientSocketTCP>
{
    return std::make_shared<ClientSocketTCP>(serverAddress, serverPort);
}

SocketContext::SocketContext()
{
    Socket::InitializeSystem();
}

SocketContext::~SocketContext()
{
    Socket::ShutdownSystem();
}

} // namespace Sock

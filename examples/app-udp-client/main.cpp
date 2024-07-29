#include <RightSockContext.hpp>

#include <iostream>
#include <memory>

int main()
{
    std::string address = "127.0.0.1";
    Sock::port_t serverPort = 8888;
    Sock::port_t clientPort = 9999;

    auto& context = Sock::RightSockContext::Instance();

    auto clientSocket = context.CreateConnectionPointUDP(address, clientPort);

    clientSocket->Send({"Client says hello :3", address, serverPort});

    auto reply = clientSocket->Receive();

    std::cout << reply.m_Message << " : [Message from " << reply.m_Address << ":" << std::to_string(reply.m_Port) << "]" << std::endl;
}
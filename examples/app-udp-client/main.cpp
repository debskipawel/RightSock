#include <RightSockContext.hpp>

#include <iostream>
#include <memory>

int main()
{
    RightSock::Address address = "127.0.0.1";
    RightSock::Port serverPort = 8888;
    RightSock::Port clientPort = 9999;

    auto& context = RightSock::Context::Instance();

    auto clientSocket = context.CreateConnectionPointUDP(address, clientPort);

    clientSocket->Send({"Client says hello :3", address, serverPort});

    auto reply = clientSocket->Receive();

    std::cout << reply.m_Message << " : [Message from " << reply.m_Address << ":" << std::to_string(reply.m_Port) << "]" << std::endl;
}
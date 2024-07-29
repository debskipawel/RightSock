#include <RightSockContext.hpp>

#include <iostream>

int main()
{
    RightSock::Address address = "127.0.0.1";
    RightSock::Port serverPort = 8888;

    auto& context = RightSock::Context::Instance();

    auto serverSocket = context.CreateConnectionPointUDP(address, serverPort);

    auto message = serverSocket->Receive();

    std::cout << message.m_Message << " : [Message from " << message.m_Address << ":" << std::to_string(message.m_Port) << "]" << std::endl;

    serverSocket->Send({"Reply sent from the server!", message.m_Address, message.m_Port});
}
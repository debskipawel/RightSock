#include <SocketContext.hpp>

#include <format>
#include <iostream>

int main()
{
    std::string address = "127.0.0.1";
    Sock::port_t port = 8888;

    auto& context = Sock::SocketContext::GetInstance();
    auto serverSocket = context.CreateServerTCP(address, port);

    auto newClient = serverSocket->WaitForConnection();
    auto message = newClient->Receive();

    std::cout << std::format("{} : [Message from {}:{}]", message.m_Message, message.m_Address, message.m_Port) << std::endl;

    auto reply = Sock::SocketPayload("Reply sent from the server!", message.m_Address, message.m_Port);
    newClient->Send(reply);
}
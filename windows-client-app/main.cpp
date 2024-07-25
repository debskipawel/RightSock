#include <SocketContext.hpp>

#include <format>
#include <iostream>

int main()
{
    std::string address = "127.0.0.1";
    Sock::port_t port = 8888;

    auto& context = Sock::SocketContext::GetInstance();
    auto clientSocket = context.ConnectToServerTCP(address, port);

    auto message = Sock::SocketPayload("Client says hello :3", address, port);
    clientSocket->Send(message);

    auto reply = clientSocket->Receive();

    std::cout << std::format("{} : [Message from {}:{}]", reply.m_Message, reply.m_Address, reply.m_Port) << std::endl;
}
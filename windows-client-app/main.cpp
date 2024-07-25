#include <TCP/ClientSocketTCP.hpp>

#include <format>
#include <iostream>

int main()
{
    std::string address = "127.0.0.1";
    Sock::port_t port = 8888;

    auto clientSocket = std::make_unique<Sock::ClientSocketTCP>(address, port);

    clientSocket->Send({"Client says hello :3", address, port});

    auto reply = clientSocket->Receive();

    std::cout << std::format("{} : [Message from {}:{}]", reply.m_Message, reply.m_Address, reply.m_Port) << std::endl;
}
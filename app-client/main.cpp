#include <TCP/ClientSocketTCP.hpp>

#include <iostream>
#include <memory>

int main()
{
    std::string address = "127.0.0.1";
    Sock::port_t port = 8888;

    Sock::Socket::InitializeSystem();

    {
        auto clientSocket = std::make_unique<Sock::ClientSocketTCP>(address, port);

        clientSocket->Send({"Client says hello :3", address, port});

        auto reply = clientSocket->Receive();

        std::cout << reply.m_Message << " : [Message from " << reply.m_Address << ":" << std::to_string(reply.m_Port) << "]" << std::endl;
    }

    Sock::Socket::ShutdownSystem();
}
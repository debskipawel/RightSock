#include <TCP/ListeningSocketTCP.hpp>

#include <iostream>

int main()
{
    std::string address = "127.0.0.1";
    Sock::port_t port = 8888;

    Sock::Socket::InitializeSystem();

    {
        auto serverSocket = std::make_unique<Sock::ListeningSocketTCP>(address, port);

        auto newClient = serverSocket->WaitForConnection();
        auto message = newClient->Receive();

        std::cout << message.m_Message << " : [Message from " << message.m_Address << ":" << std::to_string(message.m_Port) << "]" << std::endl;

        newClient->Send({"Reply sent from the server!", message.m_Address, message.m_Port});
    }

    Sock::Socket::ShutdownSystem();
}
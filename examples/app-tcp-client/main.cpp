#include <RightSock.hpp>

#include <iostream>
#include <memory>

int main()
{
    RightSock::Address address = "127.0.0.1";
    RightSock::Port port = 8888;

    auto& context = RightSock::Context::Instance();

    auto clientSocket = context.ConnectToServerTCP(address, port);

    clientSocket->Send({"Client says hello :3", address, port});

    auto [status, reply] = clientSocket->Receive();

    switch (status)
    {
        case RightSock::ReceiveStatusCode::RECEIVED:
        {
            std::cout << reply.m_Message << " : [Message from " << reply.m_Address << ":" << std::to_string(reply.m_Port) << "]" << std::endl;
            break;
        }
        case RightSock::ReceiveStatusCode::CONNECTION_CLOSED:
        {
            std::cout << "Connection was closed. Terminating.";
            break;
        }
        default:
        {
            break;
        }
    }
}
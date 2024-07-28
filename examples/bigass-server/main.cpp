#include <TCP/ListeningSocketTCP.hpp>
#include <UDP/SocketUDP.hpp>

#include <barrier>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <syncstream>
#include <thread>
#include <unordered_map>

std::queue<Sock::SocketPayload> g_ReceivedMessageQueue;
std::mutex g_ReceivedMessageQueueMutex;

std::queue<std::string> g_SentMessageQueue;
std::mutex g_SentMessageQueueMutex;
std::condition_variable g_SentMessageCV;
std::barrier<>* g_SentMessagesBarrier;

std::unordered_map<int, std::thread> g_ClientWriterThreads;
std::unordered_map<int, std::thread> g_ClientReaderThreads;
std::mutex g_ClientThreadsMutex;

std::thread g_ListeningThread;
std::thread g_ServerUDPThread;

bool g_ShouldContinue = true;
std::mutex g_ContinueFlagMutex;

std::unique_ptr<Sock::ListeningSocketTCP> g_ListeningSocket;
std::unique_ptr<Sock::SocketUDP> g_ServerUDPSocket;

void serverReaderWorkTCP(std::shared_ptr<Sock::ServerSocketTCP> serverSocketTCP)
{
    while (g_ShouldContinue)
    {
        auto message = serverSocketTCP->Receive();

        if (message.m_Message.empty())
        {
            break;
        }

        {
            auto lck = std::lock_guard<std::mutex>(g_ReceivedMessageQueueMutex);
            g_ReceivedMessageQueue.push(message);
        }

        std::cout << "[" << message.m_Address << ":" << std::to_string(message.m_Port) << "] " << message.m_Message << std::endl;

        if (message.m_Message == "QUIT")
        {
            auto lck = std::lock_guard<std::mutex>(g_ContinueFlagMutex);
            g_ShouldContinue = false;
        }
    }

    auto lck = std::lock_guard<std::mutex>(g_ClientThreadsMutex);
    g_ClientReaderThreads.erase(serverSocketTCP->Id());
}

void serverWriterWorkTCP(std::shared_ptr<Sock::ServerSocketTCP> serverSocketTCP)
{
    while (g_ShouldContinue)
    {
        std::string message;

        {
            std::unique_lock<std::mutex> lck(g_SentMessageQueueMutex);
            g_SentMessageCV.wait(lck);

            message = g_SentMessageQueue.front();
        }

        auto sendResult = serverSocketTCP->Send({message, serverSocketTCP->Address(), serverSocketTCP->Port()});

        g_SentMessagesBarrier->arrive_and_wait();

        if (sendResult == Sock::SendStatus::CONNECTION_CLOSED)
        {
            break;
        }
    }

    auto lck = std::lock_guard<std::mutex>(g_ClientThreadsMutex);
    g_ClientWriterThreads.erase(serverSocketTCP->Id());
}

void listeningWork()
{
    while (g_ShouldContinue)
    {
        auto newClient = g_ListeningSocket->WaitForConnection();

        if (!newClient)
        {
            continue;
        }

        auto newClientId = newClient->Id();

        auto lck = std::lock_guard<std::mutex>(g_ClientThreadsMutex);
        g_ClientWriterThreads.emplace(newClientId, std::thread(serverWriterWorkTCP, newClient));
        g_ClientReaderThreads.emplace(newClientId, std::thread(serverReaderWorkTCP, newClient));
    }
}

void serverUDPWork()
{
    while (g_ShouldContinue)
    {
        auto message = g_ServerUDPSocket->Receive();

        if (message.m_Message.empty())
        {
            continue;
        }

        {
            auto lck = std::lock_guard<std::mutex>(g_ReceivedMessageQueueMutex);
            g_ReceivedMessageQueue.push(message);
        }

        std::cout << "[" << message.m_Address << ":" << std::to_string(message.m_Port) << "] " << message.m_Message << std::endl;

        g_ServerUDPSocket->Send({"Copy.", message.m_Address, message.m_Port});

        if (message.m_Message == "QUIT")
        {
            auto lck = std::lock_guard<std::mutex>(g_ContinueFlagMutex);
            g_ShouldContinue = false;
        }
    }
}

int main()
{
    std::string address = "127.0.0.1";
    Sock::port_t port = 8888;

    Sock::Socket::InitializeSystem();

    g_ListeningSocket = std::make_unique<Sock::ListeningSocketTCP>(address, port);
    g_ServerUDPSocket = std::make_unique<Sock::SocketUDP>(address, port);

    g_ListeningThread = std::thread(listeningWork);
    g_ServerUDPThread = std::thread(serverUDPWork);

    while (g_ShouldContinue)
    {
        std::string message;
        std::getline(std::cin, message);

        if (message == "QUIT")
        {
            auto lck = std::lock_guard<std::mutex>(g_ContinueFlagMutex);
            g_ShouldContinue = false;
        }

        {
            auto lck = std::lock_guard<std::mutex>(g_SentMessageQueueMutex);
            g_SentMessageQueue.push(message);
        }

        size_t numberOfThreads;

        {
            auto lck = std::lock_guard<std::mutex>(g_ClientThreadsMutex);

            numberOfThreads = std::ssize(g_ClientWriterThreads);
        }

        std::barrier writerThreadBarrier(numberOfThreads + 1);
        g_SentMessagesBarrier = &writerThreadBarrier;

        g_SentMessageCV.notify_all();
        g_SentMessagesBarrier->arrive_and_wait();

        g_SentMessageQueue.pop();
    }

    g_ListeningSocket->CloseConnection();
    g_ServerUDPSocket->CloseConnection();

    g_ListeningThread.join();
    g_ServerUDPThread.join();

    Sock::Socket::ShutdownSystem();
}
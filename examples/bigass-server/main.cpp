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
std::thread g_CleanerThread;

std::queue<int> g_ReadersToErase;
std::queue<int> g_WritersToErase;
std::mutex g_EraseQueueMutex;
std::condition_variable g_EraseCV;

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
            std::lock_guard<std::mutex> lck(g_EraseQueueMutex);
            g_ReadersToErase.push(serverSocketTCP->Id());

            g_EraseCV.notify_all();

            break;
        }

        {
            auto lck = std::lock_guard<std::mutex>(g_ReceivedMessageQueueMutex);
            g_ReceivedMessageQueue.push(message);
        }

        std::cout << "[" << message.m_Address << ":" << std::to_string(message.m_Port) << "] " << message.m_Message << std::endl;
    }
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

        g_SentMessagesBarrier->arrive();

        if (sendResult == Sock::SendStatus::CONNECTION_CLOSED)
        {
            std::lock_guard<std::mutex> lck(g_EraseQueueMutex);
            g_WritersToErase.push(serverSocketTCP->Id());

            g_EraseCV.notify_all();

            break;
        }
    }
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
    }
}

void cleanerWork()
{
    while (g_ShouldContinue)
    {
        std::unique_lock<std::mutex> lck(g_EraseQueueMutex);
        g_EraseCV.wait(lck);

        std::lock_guard<std::mutex> clientsLck(g_ClientThreadsMutex);

        while (!g_ReadersToErase.empty())
        {
            g_ClientReaderThreads[g_ReadersToErase.front()].join();
            g_ClientReaderThreads.erase(g_ReadersToErase.front());

            g_ReadersToErase.pop();
        }

        while (!g_WritersToErase.empty())
        {
            g_ClientReaderThreads[g_ReadersToErase.front()].join();
            g_ClientReaderThreads.erase(g_ReadersToErase.front());

            g_ReadersToErase.pop();
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

    g_CleanerThread = std::thread(cleanerWork);

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

    g_EraseCV.notify_all();
    g_SentMessageCV.notify_all();

    g_CleanerThread.join();
    g_ListeningThread.join();
    g_ServerUDPThread.join();

    for (auto& [id, thread] : g_ClientReaderThreads)
    {
        thread.join();
    }

    for (auto& [id, thread] : g_ClientWriterThreads)
    {
        thread.join();
    }

    Sock::Socket::ShutdownSystem();
}
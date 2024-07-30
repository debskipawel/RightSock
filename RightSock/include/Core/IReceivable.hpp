#pragma once

#include <Core/SocketPayload.hpp>

namespace RightSock
{

enum class ReceiveStatusCode : int
{
    RECEIVED = 0,
    CONNECTION_CLOSED = 1,
    RECV_ERROR = 2,
};

struct ReceiveResult
{
    ReceiveStatusCode m_StatusCode;
    SocketPayload m_Payload;
};

class IReceivable
{
public:
    virtual auto Receive() const -> ReceiveResult = 0;
};

} // namespace RightSock

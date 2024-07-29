#pragma once

#include <Core/SocketPayload.hpp>

namespace RightSock
{

enum class SendStatusCode : int
{
    SENT = 0,
    CONNECTION_CLOSED = 1,
    SEND_ERROR = 2,
    VALIDATION_ERROR = 3,
};

class ISendable
{
public:
    virtual auto Send(const SocketPayload& payload) const -> SendStatusCode = 0;
};

} // namespace RightSock

#pragma once

#include <Core/SocketPayload.hpp>

namespace Sock
{

enum class SendStatus : int
{
    SENT = 0,
    CONNECTION_CLOSED = 1,
    SEND_ERROR = 2,
};

class ISendable
{
public:
    virtual auto Send(const SocketPayload& payload) const -> SendStatus = 0;
};

} // namespace Sock

#pragma once

#include <Core/SocketPayload.hpp>

namespace RightSock
{

class IReceivable
{
public:
    virtual auto Receive() const -> SocketPayload = 0;
};

} // namespace RightSock

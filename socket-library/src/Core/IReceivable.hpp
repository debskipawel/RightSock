#include <Core/SocketPayload.hpp>

namespace Sock
{

class IReceivable
{
public:
    virtual auto Receive() const -> SocketPayload = 0;
};

} // namespace Sock

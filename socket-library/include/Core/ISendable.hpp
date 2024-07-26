#include <Core/SocketPayload.hpp>

namespace Sock
{

class ISendable
{
public:
    virtual auto Send(const SocketPayload& payload) const -> void = 0;
};

} // namespace Sock

#pragma once

#include <common/constructs/Types.hpp>

namespace Server {

class ServerEngine {
public:
    ServerEngine();
    
    const u8 maxConnections;
};

}

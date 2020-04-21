#pragma once

#include "../constructs/Types.hpp"

namespace Net {

enum class ClientCommand : u8 {
    PLAYER_CONTROL
};

enum class ServerCommand : u8 {
    GAME_MAP,
    ENTITY,
    PLAYER,
    CLIENT_PLAYER
};

}

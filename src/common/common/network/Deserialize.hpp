#pragma once

#include <vector>

#include "../constructs/Types.hpp"
#include "../constructs/Entity.hpp"
#include "../constructs/GameMap.hpp"
#include "../constructs/Player.hpp"
#include "../constructs/PlayerControl.hpp"

namespace Net {

Common::Entity deserializeEntity(const std::vector<u8>& data);
Common::GameMap deserializeGameMap(const std::vector<u8>& data);
Common::Player deserializePlayer(const std::vector<u8>& data);
Common::PlayerControl deserializePlayerControl(const std::vector<u8>& data);

}

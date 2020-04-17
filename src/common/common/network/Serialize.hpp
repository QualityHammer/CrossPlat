#pragma once

#include <vector>

#include "../constructs/Types.hpp"
#include "../constructs/Entity.hpp"
#include "../constructs/GameMap.hpp"
#include "../constructs/Player.hpp"
#include "../constructs/PlayerControl.hpp"

const std::vector<u8> serialize(const Common::Entity& entity);
const std::vector<u8> serialize(const Common::GameMap& gMap);
const std::vector<u8> serialize(const Common::Player& player);
const std::vector<u8> serialize(const Common::PlayerControl& playerControl);


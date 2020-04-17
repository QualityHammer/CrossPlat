#pragma once

#include <vector>

#include "../constructs/Types.hpp"
#include "../constructs/Entity.hpp"
#include "../constructs/GameMap.hpp"

const std::vector<u8> serialize(const Common::Entity& entity);
const std::vector<u8> serialize(const Common::GameMap& gMap);

#pragma once

#include <bitset>
#include <cstdint>

using Entity              = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType                = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using EntitySignature = std::bitset<MAX_COMPONENTS>;
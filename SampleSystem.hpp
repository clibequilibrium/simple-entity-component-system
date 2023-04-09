#pragma once

#include "ECS.hpp"
#include "Components.h"

extern World world;

class SampleSystem : public System {
  public:
    void Update() override {
        for (auto const &entity : m_Entities) {
            auto       &position = world.GetComponent<Position>(entity);
            auto const &velocity = world.GetComponent<Velocity>(entity);

            position.x += velocity.x;
            position.y += velocity.y;
        }
    }
};
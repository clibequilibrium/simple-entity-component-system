#include "SampleSystem.hpp"
#include "ECS.hpp"

World world;

int main() {

    world.Init();

    world.RegisterComponent<Position>();
    world.RegisterComponent<Velocity>();

    auto sampleSystem = world.RegisterSystem<SampleSystem>();

    EntitySignature signature;
    signature.set(world.GetComponentType<Position>());
    signature.set(world.GetComponentType<Velocity>());

    world.SetSystemSignature<SampleSystem>(signature);

    auto entity = world.CreateEntity();

    world.AddComponent(entity, Position{0, 0});
    world.AddComponent(entity, Velocity{1, 2});

    sampleSystem->Update();

    const Position position = world.GetComponent<Position>(entity);

    printf("Entity's position is {%f, %f}\n", position.x, position.y);
}
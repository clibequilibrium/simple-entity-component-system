#pragma once

#include "Base.h"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include <memory>

class World {
  public:
    void Init() {
        // Create pointers to each manager
        m_ComponentManager = std::make_unique<ComponentManager>();
        m_EntityManager    = std::make_unique<EntityManager>();
        m_SystemManager    = std::make_unique<SystemManager>();
    }

    // Entity methods
    Entity CreateEntity() { return m_EntityManager->CreateEntity(); }

    void DestroyEntity(Entity entity) {
        m_EntityManager->DestroyEntity(entity);
        m_ComponentManager->OnEntityDestroyed(entity);
        m_SystemManager->OnEntityDestroyed(entity);
    }

    // Component methods
    template <typename T> void RegisterComponent() { m_ComponentManager->RegisterComponent<T>(); }

    template <typename T> void AddComponent(Entity entity, T component) {
        m_ComponentManager->AddComponent<T>(entity, component);

        auto signature = m_EntityManager->GetEntitySignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), true);

        m_EntityManager->SetEntitySignature(entity, signature);
        m_SystemManager->OnEntitySignatureChanged(entity, signature);
    }

    template <typename T> void RemoveComponent(Entity entity) {
        m_ComponentManager->RemoveComponent<T>(entity);

        auto signature = m_EntityManager->GetEntitySignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), false);

        m_EntityManager->SetEntitySignature(entity, signature);
        m_SystemManager->OnEntitySignatureChanged(entity, signature);
    }

    template <typename T> T &GetComponent(Entity entity) {
        return m_ComponentManager->GetComponent<T>(entity);
    }

    template <typename T> ComponentType GetComponentType() {
        return m_ComponentManager->GetComponentType<T>();
    }

    // System methods
    template <typename T> std::shared_ptr<T> RegisterSystem() {
        return m_SystemManager->RegisterSystem<T>();
    }

    template <typename T> void SetSystemSignature(EntitySignature signature) {
        m_SystemManager->SetEntitySignature<T>(signature);
    }

  private:
    std::unique_ptr<ComponentManager> m_ComponentManager;
    std::unique_ptr<EntityManager>    m_EntityManager;
    std::unique_ptr<SystemManager>    m_SystemManager;
};
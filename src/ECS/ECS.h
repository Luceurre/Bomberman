//
// Created by julien on 18/04/2020.
//
#pragma once
#ifndef ATELIERPROG_ECS_H
#define ATELIERPROG_ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <queue>
#include "../Utils/Logger.h"

class Component;
class Entity;
class Manager;

using ComponentID = size_t;
using Group = size_t;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component : public Logger {
protected:
    inline std::string descriptor() override {
        return "(Component)";
    }
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    // à retirer une fois que le système d'event est en place!
    inline virtual void handleEvent(const SDL_Event& event) {}

    virtual ~Component() {}
};

class Entity {
protected:
    Manager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
public:
    Entity(Manager& mManager) : manager(mManager) {
        priority = 0;
    }

    void update() {
        for (auto& c : components) c->update();
    }
    void draw() {
        for (auto& c : components) c->draw();
    }

    inline void spreadEvent(const SDL_Event& event) {
        for (auto& c : components) c->handleEvent(event);
    }

    bool isActive() const { return active; }
    void destroy() { active = false; }

    bool hasGroup(Group mGroup) {
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup) {
        groupBitSet[mGroup] = false;
    }

    template <typename T> bool hasComponent() const {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponents(TArgs&&... mArgs) {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T> T& getComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    inline friend bool operator<(const Entity& l, const Entity& r) {
        return l.priority < r.priority;
    }

    int priority;
};

class Manager {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
    void update() {
        for (auto& e : entities) {e->update();}
    }

    void draw() {
        for (auto& e : entities) {e->draw();}
    }

    inline void spreadEvent(const SDL_Event& event) {
        for (auto& e : entities) {e->spreadEvent(event);}
    }

    void refresh() {

        for (auto i(0u); i < maxGroups; i++) {
            auto& v(groupedEntities[i]);
            v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
            {
                return !mEntity->isActive() || !mEntity->hasGroup(i);
            }),
                std::end(v));
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) {
            return !mEntity->isActive();
        }),
        std::end(entities));
    }

    void AddToGroup(Entity* mEntity, Group mGroup) {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup) {
        return groupedEntities[mGroup];
    }

    Entity& addEntity()
    {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));

        std::push_heap(entities.begin(), entities.end());

        return *e;
    }
};


#endif //ATELIERPROG_ECS_H

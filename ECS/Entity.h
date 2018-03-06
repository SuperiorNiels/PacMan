//
// Created by niels on 04/03/18.
//

#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H


#include <vector>
#include "Component.h"

using entityID = int16_t;

inline entityID getEntityID() {
    static entityID id = 0;
    return id++;
};

class Entity {
public:
    void addComponent(Component* c);
    template <class T> T* getComponentById(componentID id);
    template <class T> T* getComponentByType(int8_t type);
    void removeComponentById(componentID id);
    void removeComponentByType(int8_t type);
    ~Entity();
    entityID id = getEntityID();
private:
    std::vector<Component*> components;
};

inline Entity::~Entity()
{
    for(auto& c : components)
        delete c;
    components.clear();
};

inline void Entity::addComponent(Component *c)
{
    if(getComponentByType<Component>(c->type) == nullptr)
    {
        components.push_back(c);
    }
}

template <class T>
T* Entity::getComponentById(componentID id)
{
    for(auto& c : components)
    {
        if(c->id == id)
        {
            return dynamic_cast<T*>(c);
        }
    }
    return nullptr;
}

template <class T>
T* Entity::getComponentByType(int8_t type)
{
    for(auto& c : components)
    {
        if(c->type == type)
        {
            return dynamic_cast<T*>(c);
        }
    }
    return nullptr;
}

inline void Entity::removeComponentById(componentID id)
{
    for(auto it = components.begin(); it < components.end(); it++)
    {
        if(it.operator*()->id == id)
        {
            components.erase(it);
            delete it.operator*();
            break;
        }
    }
}

inline void Entity::removeComponentByType(int8_t type)
{
    for(auto it = components.begin(); it < components.end(); it++)
    {
        if(it.operator*()->type == type)
        {
            components.erase(it);
            delete it.operator*();
            break;
        }
    }
}

#endif //ECS_ENTITY_H

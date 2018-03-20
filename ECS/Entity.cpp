//
// Created by niels on 15/03/18.
//

#include "Entity.h"

Entity::~Entity()
{
    for(auto& c : components)
        delete c;
    components.clear();
};

void Entity::addComponent(Component *c)
{
    if(getComponentByType<Component>(c->type) == nullptr)
    {
        components.push_back(c);
    }
}

bool Entity::hasComponentType(int8_t type)
{
    for(auto& c : components)
    {
        if(c->type == type)
        {
            return true;
        }
    }
    return false;
}

bool Entity::hasComponentTypes(std::vector<int8_t> types)
{
    for(auto it = types.begin(); it < types.end(); it++)
    {
        if(hasComponentType(it.operator*()))
        {
            types.erase(it);
            it--;
        }
        if(types.empty())
            return true;
    }
    return false;
}

void Entity::removeComponentByType(int8_t type)
{
    for(auto it = components.begin(); it < components.end(); it++)
    {
        if(it.operator*()->type == type)
        {
            delete it.operator*();
            components.erase(it);
            break;
        }
    }
}

const int Entity::getComponentsSize()
{
    return (int)components.size();
}

void Entity::clearComponents()
{
    for(auto* c : components)
    {
        delete c;
    }
    components.clear();
}


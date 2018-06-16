//
// Created by niels on 15/03/18.
//

#include "../../include/ECS/Entity.h"

namespace ECS
{
    Entity::~Entity()
    {
        clearComponents();
    };

    void Entity::addComponent(Component *c)
    {
        if(getComponentByType<Component>(c->type) == nullptr)
        {
            components[c->type] = c;
        }
    }

    bool Entity::hasComponentType(int8_t type)
    {
        return components.find(type) != components.end();
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
        }
        return types.empty();
    }

    void Entity::destoryComponentByType(int8_t type)
    {
        if(hasComponentType(type))
        {
            delete components[type];
            auto it = components.find(type);
            components.erase(it);
        }
    }

    void Entity::removeComponentByType(int8_t type)
    {
        if(hasComponentType(type))
        {
            auto it = components.find(type);
            components.erase(it);
        }
    }


    const int Entity::getComponentsSize()
    {
        return (int)components.size();
    }

    void Entity::clearComponents()
    {
        for(auto it : components)
        {
            delete it.second;
        }
        components.clear();
    }
}
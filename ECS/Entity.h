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
    template <class T> T* getComponentByType(int8_t type);
    bool hasComponentType(int8_t type);
    bool hasComponentTypes(std::vector<int8_t> types);
    void removeComponentByType(int8_t type);
    const int getComponentsSize();
    void clearComponents();
    ~Entity();
    entityID id = getEntityID();
private:
    std::vector<Component*> components;
};

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

#endif //ECS_ENTITY_H

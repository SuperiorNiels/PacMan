//
// Created by niels on 04/03/18.
//

#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include <iostream>

using componentID = int16_t;

inline componentID getComponentID() {
    static componentID id = 0;
    return id++;
};

class Component
{
public:
    componentID id = getComponentID();
    int8_t type = -1;
    virtual ~Component() = default;
};

class PositionComponent : public Component
{
public:
    PositionComponent() { type = 0; };
    int x = 0;
    int y = 0;
};

class RenderComponent : public Component
{
public:
    RenderComponent() { type = 1; };
    std::string image = "./";
};

#endif //ECS_COMPONENT_H

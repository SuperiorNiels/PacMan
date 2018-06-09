//
// Created by niels on 04/03/18.
//

#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include <iostream>

namespace ECS
{
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
}


#endif //ECS_COMPONENT_H

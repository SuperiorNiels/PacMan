//
// Created by niels on 06/03/18.
//

#ifndef ECS_PACMAN_COMPONENTS_H
#define ECS_PACMAN_COMPONENTS_H

#include "ECS/ECS.h"

class PositionComponent : public Component
{
public:
    PositionComponent() { type = 0; };
    int x = 0;
    int y = 0;
};



#endif //ECS_PACMAN_COMPONENTS_H

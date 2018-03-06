//
// Created by niels on 06/03/18.
//

#ifndef ECS_PACMAN_COMPONENTS_H
#define ECS_PACMAN_COMPONENTS_H

#include "ECS/ECS.h"

/*
 * types:
 *  0 - position
 *  1 - movable
 *  2 - AI
 */

class PositionComponent : public Component
{
public:
    PositionComponent() { type = 0; };
    int x = 0;
    int y = 0;
};

class MovableComponent : public Component
{
public:
    MovableComponent() { type = 1; };
    int x_speed = 0;
    int y_speed = 0;
};

class AIComponent : public Component
{
public:
    AIComponent() { type = 2; }
    int count = 0;
};

// TODO: make event input component

#endif //ECS_PACMAN_COMPONENTS_H

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
 *  2 - player input
 *  3 - ai
 *  10 - render
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

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent() { type = 2;}
};

class AIComponent : public Component
{
public:
    AIComponent() { type = 3; }
    int count = 0;
    int length = 50;
};

class RenderComponent : public Component
{
public:
    RenderComponent() { type = 10; }
    int width = 0;
    int height = 0;
    int animation_length = 1;
    int animation_speed = 10;
    int current_frame = 0;
    int count = 0;
    int frame_offset = 0;
    int direction_offsets[4] = {0,0,0,0}; // left,right,up,down
};


#endif //ECS_PACMAN_COMPONENTS_H

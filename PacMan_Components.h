//
// Created by niels on 06/03/18.
//

#ifndef ECS_PACMAN_COMPONENTS_H
#define ECS_PACMAN_COMPONENTS_H

#include "ECS/ECS.h"

enum ComponentTypes
{
    POSITION_COMPONENT,
    MOVABLE_COMPONENT,
    PLAYER_INPUT_COMPONENT,
    AI_COMPONENT,
    RENDER_COMPONENT,
};

class PositionComponent : public Component
{
public:
    PositionComponent() { type = POSITION_COMPONENT; };
    int x = 0;
    int y = 0;
};

class MovableComponent : public Component
{
public:
    MovableComponent() { type = MOVABLE_COMPONENT; };
    int x_speed = 0;
    int y_speed = 0;
};

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent() { type = PLAYER_INPUT_COMPONENT;}
};

class AIComponent : public Component
{
public:
    AIComponent() { type = AI_COMPONENT; }
    int count = 0;
    int length = 50;
};

class RenderComponent : public Component
{
public:
    RenderComponent() { type = RENDER_COMPONENT; }
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

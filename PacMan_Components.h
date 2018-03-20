//
// Created by niels on 06/03/18.
//

#ifndef ECS_PACMAN_COMPONENTS_H
#define ECS_PACMAN_COMPONENTS_H

#include "ECS/ECS.h"
#include "PacMan_Constants.h"
#include "Systems/CollisionSystem.h"

enum ComponentTypes
{
    POSITION_COMPONENT,
    MOVABLE_COMPONENT,
    PLAYER_INPUT_COMPONENT,
    AI_COMPONENT,
    RENDER_COMPONENT,
    COLLISION_COMPONENT,
    POINTS_COMPONENT
};

class PositionComponent : public Component
{
public:
    PositionComponent() { type = POSITION_COMPONENT; };
    double x = 0;
    double y = 0;
};

class MovableComponent : public Component
{
public:
    MovableComponent() { type = MOVABLE_COMPONENT; };
    double x_speed = 0;
    double y_speed = 0;
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
    int length = 1;
};

class RenderComponent : public Component
{
public:
    RenderComponent() { type = RENDER_COMPONENT; }
    int width = 0;
    int height = 0; // fixme: width en height nodig?
    bool visible = true;
    int animation_length = 1;
    int animation_speed = 10;
    int current_frame = 0;
    int count = 0;
    int frame_offset = 0;
    int direction_offsets[4] = {0,0,0,0}; // left,right,up,down
    double scale = 1;
};

class CollisionComponent : public Component
{
public:
    CollisionComponent() { type = COLLISION_COMPONENT; }
    int collision_box[4] = {0,0,0,0}; // x offset, y_offset, width, height
};

class PointsComponent : public Component
{
public:
    PointsComponent() { type = POINTS_COMPONENT; }
    int points = 0;
};


#endif //ECS_PACMAN_COMPONENTS_H

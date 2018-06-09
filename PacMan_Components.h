//
// Created by niels on 06/03/18.
//

#ifndef ECS_PACMAN_COMPONENTS_H
#define ECS_PACMAN_COMPONENTS_H

#include "ECS/ECS.h"
#include "PacMan_Constants.h"
#include "Systems/CollisionSystem.h"
#include "World.h"
#include "Systems/TimerSystem.h"

using namespace ECS;

enum ComponentTypes
{
    POSITION_COMPONENT,
    MOVABLE_COMPONENT,
    PLAYER_INPUT_COMPONENT,
    AI_COMPONENT,
    RENDER_COMPONENT,
    COLLISION_COMPONENT,
    ENERGIZER_COMPONENT,
    POINTS_COMPONENT,
    SCORE_COMPONENT,
    LIVES_COMPONENT,
    TEXT_COMPONENT
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
    direction current_dir = STOP;
    direction wanted_dir = STOP;
    double speed = 1;
    double time = 0;
    entity_movable_state state = IDLE;
    int x_prev = 0;
    int y_prev = 0;
};

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent() { type = PLAYER_INPUT_COMPONENT; };
};

class AIComponent : public Component
{
public:
    AIComponent() { type = AI_COMPONENT; };
    ai_states state = HOME;
    int target_x = 0;
    int target_y = 0;
    int home_x = 0;
    int home_y = 0;
    int scatter_x = 0;
    int scatter_y = 0;
    int leave_x = 0;
    int leave_y = 0;
    direction previous = STOP;
    TimerSystem* timer = nullptr;
    int score_before_leave = 200;
    bool go_next_state = true;
    int time_to_wait = 7000;
    Entity* player = nullptr;
};

class RenderComponent : public Component
{
public:
    RenderComponent() { type = RENDER_COMPONENT; };
    bool visible = true;
    int animation_length = 1;
    int animation_speed = 10;
    int current_frame = 0;
    int count = 0;
    int frame_offset = 0;
    int direction_offsets[4] = {0,0,0,0}; // left,right,up,down
    double scale = 1;
    double x_render_offset = 0;
    double y_render_offset = 0;
};

class CollisionComponent : public Component
{
public:
    CollisionComponent() { type = COLLISION_COMPONENT; };
    clip collision_box; // x_offset, y_offset, width, height
};

class PointsComponent : public Component
{
public:
    PointsComponent() { type = POINTS_COMPONENT; };
    int points = 0;
};

class EnergizerComponent : public Component
{
public:
    EnergizerComponent() { type = ENERGIZER_COMPONENT; };
    int points = 400;
};

class ScoreComponent : public Component
{
public:
    ScoreComponent() { type = SCORE_COMPONENT; };
    int score = 0;
};

class LivesComponent : public Component
{
public:
    LivesComponent() { type = LIVES_COMPONENT; };
    int lives = 0;
    int start_x = 0; // keep starting position, when player dies use this to 'teleport' player
    int start_y = 0;
};

class TextComponent : public Component
{
public:
    TextComponent() { type = TEXT_COMPONENT; };
    std::string text;
    int x_pos = 0;
    int y_pos = 0;
};


#endif //ECS_PACMAN_COMPONENTS_H

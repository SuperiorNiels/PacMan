//
// Created by niels on 07/03/18.
//

#ifndef ECS_PACMAN_CONSTANTS_H
#define ECS_PACMAN_CONSTANTS_H

enum direction
{
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum entity_movable_state
{
    IDLE,
    MOVING
};

enum ai_states
{
    HOME,
    SCATTER,
    CHASE,
    FLEE
};

enum game_state
{
    PAUSED,
    PLAYING,
    MENU
};

// enum direction gives location of the move vector
static const int movement_vector[5][2] = {{0,0},{-1,0},{1,0},{0,-1},{0,1}};

struct clip
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
};

#endif //ECS_PACMAN_CONSTANTS_H

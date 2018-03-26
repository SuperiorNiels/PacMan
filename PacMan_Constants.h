//
// Created by niels on 07/03/18.
//

#ifndef ECS_PACMAN_CONSTANTS_H
#define ECS_PACMAN_CONSTANTS_H

enum ghost_color
{
    RED_GHOST,
    PINK_GHOST,
    BLUE_GHOST,
    ORANGE_GHOST
};

enum direction
{
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// enum direction gives location of the move vector
static const int movement_vector[5][2] = {{0,0},{-1,0},{1,0},{0,-1},{0,1}};

struct clip
{
    double x = 0;
    double y = 0;
    double w = 0;
    double h = 0;
};

#endif //ECS_PACMAN_CONSTANTS_H

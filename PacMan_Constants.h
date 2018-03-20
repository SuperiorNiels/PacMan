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

struct clip
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
};

#endif //ECS_PACMAN_CONSTANTS_H

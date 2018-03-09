//
// Created by niels on 07/03/18.
//

#ifndef ECS_PACMAN_CONSTANTS_H
#define ECS_PACMAN_CONSTANTS_H

static float SCALE_FACTOR = 2.5;
static float WINDOW_WIDTH = 224 * SCALE_FACTOR; // 224
static float WINDOW_HEIGHT = 248 * SCALE_FACTOR; // 248

enum ghost_color
{
    RED_GHOST,
    PINK_GHOST,
    BLUE_GHOST,
    ORANGE_GHOST
};

static int pacman[12][4] = {
        {489,1,13,13},
        {473,1,13,13},
        {457,1,13,13},
        {489,1,13,13},
        {473,17,13,13},
        {457,17,13,13},
        {489,1,13,13},
        {473,34,13,13},
        {457,34,13,13},
        {489,1,13,13},
        {473,49,13,13},
        {457,49,13,13},
};

static int ghost[8][4] = {
        {457,65,14,13},
        {473,65,14,13},
        {489,65,14,13},
        {505,65,14,13},
        {521,65,14,13},
        {537,65,14,13},
        {553,65,14,13},
        {569,65,14,13},
};

#endif //ECS_PACMAN_CONSTANTS_H

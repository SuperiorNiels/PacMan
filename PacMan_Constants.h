//
// Created by niels on 07/03/18.
//

#ifndef ECS_PACMAN_CONSTANTS_H
#define ECS_PACMAN_CONSTANTS_H

static float SCALE_FACTOR = 2;
static float WINDOW_WIDTH = 224 * SCALE_FACTOR; // 224
static float WINDOW_HEIGHT = 248 * SCALE_FACTOR; // 248

static int pacman[12][4] = {
        {489,1,14,14},
        {473,1,14,13},
        {457,1,14,13},
        {489,1,14,13},
        {473,17,14,13},
        {457,17,14,13},
        {489,1,14,13},
        {473,34,14,13},
        {457,34,14,13},
        {489,1,14,13},
        {473,49,14,13},
        {457,49,14,13},
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

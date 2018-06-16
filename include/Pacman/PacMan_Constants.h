//
// Created by niels on 07/03/18.
//

#ifndef ECS_PACMAN_CONSTANTS_H
#define ECS_PACMAN_CONSTANTS_H

namespace Pacman {
    enum direction {
        STOP,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum entity_movable_state {
        IDLE,
        MOVING
    };

    enum ai_states {
        HOME,
        LEAVE,
        RETURN,
        SCATTER,
        CHASE,
        FLEE
    };

    enum ghost_type {
        RED,
        PINK,
        BLUE,
        ORANGE
    };

    enum events_numbers {
        PAUSE_GAME,
        RESTART,
        RESET, // when pacman dies
        TEST
    };

    // enum direction gives location of the move vector
    static const int movement_vector[5][2] = {{0,  0},
                                              {-1, 0},
                                              {1,  0},
                                              {0,  -1},
                                              {0,  1}};

    struct clip {
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
    };
};

#endif //ECS_PACMAN_CONSTANTS_H

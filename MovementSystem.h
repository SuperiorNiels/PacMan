//
// Created by niels on 05/03/18.
//

#ifndef ECS_MOVEMENTSYSTEM_H
#define ECS_MOVEMENTSYSTEM_H


#include "PacMan_Components.h"

class MovementSystem : public System {
public:
    MovementSystem();
    void update() override;
};


#endif //ECS_MOVEMENTSYSTEM_H

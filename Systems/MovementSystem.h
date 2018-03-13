//
// Created by niels on 05/03/18.
//

#ifndef ECS_MOVEMENTSYSTEM_H
#define ECS_MOVEMENTSYSTEM_H


#include "../PacMan_Components.h"
#include "../World.h"

class MovementSystem : public System {
public:
    MovementSystem() = delete;
    explicit MovementSystem(World* world);
    void update() override;
private:
    World* world = nullptr;
};


#endif //ECS_MOVEMENTSYSTEM_H

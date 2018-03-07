//
// Created by niels on 07/03/18.
//

#ifndef ECS_COLLISIONSYSTEM_H
#define ECS_COLLISIONSYSTEM_H

#include "ECS/ECS.h"
#include "SDL2/SDL.h"
#include "PacMan_Components.h"
#include "PacMan_Constants.h"

class CollisionSystem : public System
{
public:
    CollisionSystem();
    void update() override;
    bool checkCollision(SDL_Rect a, SDL_Rect b);

    SDL_Renderer* renderer = nullptr;
};


#endif //ECS_COLLISIONSYSTEM_H

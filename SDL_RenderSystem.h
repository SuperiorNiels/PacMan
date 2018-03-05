//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_RENDERSYSTEM_H
#define ECS_SDL_RENDERSYSTEM_H


#include <SDL_render.h>
#include "ECS/System.h"

class SDL_RenderSystem : public System
{
public:
    SDL_Renderer* renderer;

    void update() override;
};


#endif //ECS_SDL_RENDERSYSTEM_H

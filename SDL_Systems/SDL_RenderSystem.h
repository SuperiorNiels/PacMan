//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_RENDERSYSTEM_H
#define ECS_SDL_RENDERSYSTEM_H


#include "../SDL_Components.h"
#include "../PacMan_Components.h"

class SDL_RenderSystem : public System
{
public:
    explicit SDL_RenderSystem();
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    void update() override;
    ~SDL_RenderSystem() override;
private:
    void renderCollisionBox(Entity* e);
};


#endif //ECS_SDL_RENDERSYSTEM_H

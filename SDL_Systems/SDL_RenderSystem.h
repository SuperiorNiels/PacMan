//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_RENDERSYSTEM_H
#define ECS_SDL_RENDERSYSTEM_H


#include "../SDL_Components.h"
#include "../PacMan_Components.h"
#include "../World.h"

class SDL_RenderSystem : public System
{
public:
    SDL_RenderSystem() = delete;
    explicit SDL_RenderSystem(World* world, int screen_width, int screen_height);
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    void update() override;
    ~SDL_RenderSystem() override;
private:
    void renderCollisionBox(Entity* e);
    int tile_width = 0; // square : width = height
};


#endif //ECS_SDL_RENDERSYSTEM_H

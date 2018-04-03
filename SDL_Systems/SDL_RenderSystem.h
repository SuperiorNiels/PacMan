//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_RENDERSYSTEM_H
#define ECS_SDL_RENDERSYSTEM_H


#include "../SDL_Components.h"
#include "../PacMan_Components.h"
#include "../World.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/TimerSystem.h"

class SDL_RenderSystem : public RenderSystem
{
public:
    SDL_RenderSystem(World* world, int screen_width, int screen_height, TimerSystem* timer);
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    void update() override;
    ~SDL_RenderSystem() override;
private:
    void renderCollisionBox(Entity* e);
};


#endif //ECS_SDL_RENDERSYSTEM_H

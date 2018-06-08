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
    void update() override;
    ~SDL_RenderSystem() override;
    SDL_Renderer* renderer = nullptr;
private:
    void renderBox(SDL_Rect* box, Entity* e);
    void renderScore(Entity* e);
    void renderLives(Entity* e);
    void renderText(Entity* e);
    SDL_Window* window = nullptr;
    SDL_Rect getPosition(Entity* e);
    SDL_Rect getClip(Entity* e);
};


#endif //ECS_SDL_RENDERSYSTEM_H

//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_FACTORY_H
#define ECS_SDL_FACTORY_H

#include <iostream>
#include <unordered_map>
#include "AbstractFactory.h"
#include "SDL_Systems/SDL_RenderSystem.h"
#include "SDL_Components.h"
#include "SDL_Systems/SDL_EventSystem.h"
#include "SDL_Systems/SDL_TimerSystem.h"

class SDL_Factory : public AbstractFactory {
public:
    Entity* createPacMan(int x,int y) override;
    Entity* createGhost(int x,int y, ghost_color color) override;
    RenderSystem* createRenderSystem(World* world, int screen_width, int screen_height) override;
    EventSystem* createEventSystem(double speed) override;
    TimerSystem* createTimerSystem(int fps) override;
    std::vector<Entity *> createWorldEntities(World *world) override;
    ~SDL_Factory() override;
private:
    SDL_RenderComponent* createRenderComponent(std::string path, std::vector<SDL_Rect*> clips = std::vector<SDL_Rect*>());
    SDL_RenderSystem* renderSystem = nullptr;
    std::unordered_map<std::string,SDL_Texture*> loadedTextures = std::unordered_map<std::string,SDL_Texture*>();
};


#endif //ECS_SDL_FACTORY_H

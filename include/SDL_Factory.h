//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_FACTORY_H
#define ECS_SDL_FACTORY_H

#include <iostream>
#include <unordered_map>
#include "AbstractFactory.h"
#include "Pacman/SDL_Components.h"
#include "SDL_Systems/SDL_RenderSystem.h"
#include "SDL_Systems/SDL_EventSystem.h"
#include "SDL_Systems/SDL_TimerSystem.h"
#include "Config.h"

class Config;

using namespace SDL_Systems;

class SDL_Factory : public AbstractFactory
{
public:
    SDL_Factory() = delete;

    explicit SDL_Factory(Config *config) { SDL_Factory::config = config; };

    EventSystem *createEventSystem(std::map<events_numbers, bool> *events) override;

    TimerSystem *createTimerSystem(int fps) override;

    std::vector<Entity *> createWorldEntities(World *world) override;

    RenderSystem *createRenderSystem(World *world, int screen_width, int screen_height, TimerSystem *timer, std::map<events_numbers, bool> *events) override;

    RenderComponent *createRenderComponent(std::string path, std::vector<clip> clips, std::vector<clip> death_clips) override;

    PlayerComponent *createPlayerComponent() override;

    TextComponent *createTextComponent() override;

    ~SDL_Factory() override;

private:
    void clearTextures();

    Config *config = nullptr;
    SDL_RenderSystem *renderSystem = nullptr;
    std::map<std::string, SDL_Texture *> loadedTextures;
    std::string font = "../data/Joystix.TTF"; // fixme: in config file?
};

#endif // ECS_SDL_FACTORY_H

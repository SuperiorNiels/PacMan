//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_FACTORY_H
#define ECS_SDL_FACTORY_H

#include <iostream>
#include <unordered_map>
#include "AbstractFactory.h"
#include "SDL_Components.h"
#include "SDL_Systems/SDL_RenderSystem.h"
#include "SDL_Systems/SDL_EventSystem.h"
#include "SDL_Systems/SDL_TimerSystem.h"
#include "Config.h"

class Config;

class SDL_Factory : public AbstractFactory
{
public:
    SDL_Factory() = delete;
    explicit SDL_Factory(Config* config) { SDL_Factory::config = config; };
    EventSystem* createEventSystem() override;
    TimerSystem* createTimerSystem(int fps) override;
    std::vector<Entity *> createWorldEntities(World *world) override;
    RenderSystem* createRenderSystem(World* world, int screen_width, int screen_height, TimerSystem* timer) override;
    RenderComponent* createRenderComponent(std::string path, std::vector<clip> clips) override;
    ScoreComponent* createScoreComponent(std::string font, int font_size) override;
    LivesComponent* createLivesComponent(std::string font, int font_size) override;
    TextComponent* createTextComponent(std::string font, int font_size) override;
    ~SDL_Factory() override;
private:
    void clearTextures();
    Config* config = nullptr;
    Entity* player = nullptr; // Keep track of player entity, for ai entity initialization
    SDL_RenderSystem* renderSystem = nullptr;
    std::unordered_map<std::string,SDL_Texture*> loadedTextures;
};


#endif //ECS_SDL_FACTORY_H

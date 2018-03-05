//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_FACTORY_H
#define ECS_SDL_FACTORY_H

#include "AbstractFactory.h"
#include "SDL_RenderSystem.h"
#include "SDL_Components.h"

class SDL_Factory : public AbstractFactory {
public:
    Entity* createPacMan() override;
    System* createRenderSystem() override;
private:
    SDL_RenderComponent* createRenderComponent(std::string path);
    SDL_RenderSystem* renderSystem = nullptr;
};


#endif //ECS_SDL_FACTORY_H

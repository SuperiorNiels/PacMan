//
// Created by niels on 05/03/18.
//

#ifndef ECS_ABSTRACTFACTORY_H
#define ECS_ABSTRACTFACTORY_H

#include "Pacman/World.h"
#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Systems/EventSystem.h"
#include "Systems/TimerSystem.h"
#include "Systems/RenderSystem.h"
#include "Pacman/PacMan_Components.h"

using namespace Pacman;

class AbstractFactory {
public:
    AbstractFactory() = default;

    virtual Systems::RenderSystem *
    createRenderSystem(World *world, int screen_width, int screen_height, Systems::TimerSystem *timer) = 0;

    virtual Systems::EventSystem *createEventSystem(std::map<events_numbers, bool> *events) = 0;

    virtual Systems::TimerSystem *createTimerSystem(int fps) = 0;

    virtual PlayerComponent *createPlayerComponent() = 0;

    virtual RenderComponent *createRenderComponent(std::string path, std::vector<clip> clips) = 0;

    virtual TextComponent *createTextComponent() = 0;

    virtual std::vector<Entity *> createWorldEntities(World *world) = 0;

    virtual ~AbstractFactory() = default;
};


#endif //ECS_ABSTRACTFACTORY_H

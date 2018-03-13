//
// Created by niels on 05/03/18.
//

#ifndef ECS_ABSTRACTFACTORY_H
#define ECS_ABSTRACTFACTORY_H


#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Systems/EventSystem.h"
#include "PacMan_Constants.h"
#include "Systems/TimerSystem.h"
#include "World.h"
#include "Systems/RenderSystem.h"

class AbstractFactory {
public:
    virtual Entity* createPacMan(int x, int y) = 0;
    virtual Entity* createGhost(int x, int y, ghost_color color) = 0;
    virtual RenderSystem* createRenderSystem(World* world, int screen_width, int screen_height) = 0;
    virtual EventSystem* createEventSystem(double speed) = 0;
    virtual TimerSystem* createTimerSystem(int fps) = 0;
    virtual std::vector<Entity*> createWorld(World* world) = 0;
    virtual ~AbstractFactory() = default;
};


#endif //ECS_ABSTRACTFACTORY_H

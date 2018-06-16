//
// Created by niels on 05/03/18.
//

#ifndef ECS_ABSTRACTFACTORY_H
#define ECS_ABSTRACTFACTORY_H

#include "World.h"
#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Systems/EventSystem.h"
#include "Systems/TimerSystem.h"
#include "Systems/RenderSystem.h"
#include "PacMan_Components.h"

class AbstractFactory
{
public:
    AbstractFactory() = default;
    virtual RenderSystem* createRenderSystem(World* world, int screen_width, int screen_height, TimerSystem* timer) = 0;

    virtual EventSystem *createEventSystem(std::map<events_numbers, bool> *events) = 0;
    virtual TimerSystem* createTimerSystem(int fps) = 0;

    virtual ScoreComponent *createScoreComponent() = 0;

    virtual LivesComponent *createLivesComponent() = 0;
    virtual RenderComponent* createRenderComponent(std::string path, std::vector<clip> clips) = 0;

    virtual TextComponent *createTextComponent() = 0;
    virtual std::vector<Entity*> createWorldEntities(World *world) = 0;
    virtual ~AbstractFactory() = default;
};


#endif //ECS_ABSTRACTFACTORY_H

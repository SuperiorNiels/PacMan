//
// Created by niels on 05/03/18.
//

#ifndef ECS_ABSTRACTFACTORY_H
#define ECS_ABSTRACTFACTORY_H


#include "ECS/Entity.h"
#include "ECS/System.h"
#include "EventSystem.h"

class AbstractFactory {
public:
    virtual Entity* createPacMan(int x, int y) = 0;
    virtual Entity* createGhost(int x, int y) = 0;
    virtual System* createRenderSystem() = 0;
    virtual EventSystem* createEventSystem() = 0;
    virtual ~AbstractFactory() = default;
};


#endif //ECS_ABSTRACTFACTORY_H

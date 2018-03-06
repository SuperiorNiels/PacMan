//
// Created by niels on 05/03/18.
//

#ifndef ECS_ABSTRACTFACTORY_H
#define ECS_ABSTRACTFACTORY_H


#include "ECS/Entity.h"
#include "ECS/System.h"

class AbstractFactory {
public:
    virtual Entity* createPacMan() = 0;
    virtual Entity* createGhost() = 0;
    virtual System* createRenderSystem() = 0;
};


#endif //ECS_ABSTRACTFACTORY_H

//
// Created by niels on 04/03/18.
//

#ifndef ECS_POSITIONSYSTEM_H
#define ECS_POSITIONSYSTEM_H


#include "System.h"

class PositionSystem : public System
{
public:
    void update() override;
};


#endif //ECS_POSITIONSYSTEM_H

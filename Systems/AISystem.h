//
// Created by niels on 06/03/18.
//

#ifndef ECS_AISYSTEM_H
#define ECS_AISYSTEM_H

#include "../ECS/ECS.h"
#include "../PacMan_Components.h"

class AISystem : public System {
public:
    AISystem();
    void update() override;
};


#endif //ECS_AISYSTEM_H

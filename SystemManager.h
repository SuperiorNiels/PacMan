//
// Created by niels on 05/03/18.
//

#ifndef ECS_SYSTEMMANAGER_H
#define ECS_SYSTEMMANAGER_H


#include "ECS/ECS.h"
#include <unordered_set>

class SystemManager {
public:
    void registerSystem(System* s);
    void registerEntity(Entity* e);
    void unregisterEntity(Entity* e);
private:
    std::unordered_set<System*> systems = std::unordered_set<System*>();
};


#endif //ECS_SYSTEMMANAGER_H

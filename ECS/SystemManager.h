//
// Created by niels on 05/03/18.
//

#ifndef ECS_SYSTEMMANAGER_H
#define ECS_SYSTEMMANAGER_H


#include "ECS.h"
#include <unordered_set>
#include <set>

class SystemManager {
public:
    void updateSystems();
    void registerSystem(System* s);
    void registerEntity(Entity* e);
    void unregisterEntity(Entity* e);
    ~SystemManager();
private:
    std::vector<System*> systems = std::vector<System*>();
    std::unordered_set<Entity*> entities = std::unordered_set<Entity*>();
};


#endif //ECS_SYSTEMMANAGER_H

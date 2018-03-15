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
    void updateEntities();
    void registerSystem(System* s);
    void registerEntity(Entity* e);
    void unregisterEntity(Entity* e);
    void clearEnities();
    ~SystemManager();
private:
    std::vector<System*> systems = std::vector<System*>();
    std::set<Entity*> entities = std::set<Entity*>();
};


#endif //ECS_SYSTEMMANAGER_H

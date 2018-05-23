//
// Created by niels on 05/03/18.
//

#ifndef ECS_SYSTEMMANAGER_H
#define ECS_SYSTEMMANAGER_H


#include <map>
#include "ECS.h"
#include "../PacMan_Components.h"

class SystemManager {
public:
    void updateSystems();
    void updateEntities();
    void registerSystem(System* s);
    void registerEntity(Entity* e);
    void unregisterEntity(Entity* e);
    void clearEntities();
    void removeSystem(System* s);
    ~SystemManager();
private:
    std::vector<System*> systems = std::vector<System*>();
    std::map<entityID, Entity*> entities;
};


#endif //ECS_SYSTEMMANAGER_H

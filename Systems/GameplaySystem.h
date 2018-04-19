//
// Created by niels on 19.04.18.
//

#ifndef PACMAN_GAMEPLAYSYSTEM_H
#define PACMAN_GAMEPLAYSYSTEM_H


#include "../ECS/ECS.h"
#include "../PacMan_Components.h"

class GameplaySystem : public System
{
public:
    GameplaySystem();
    void update() override;
    void addEntity(Entity* e) override;
    void removeEntity(entityID id) override;
    bool entityInSystem(entityID id) override;
private:
    std::vector<Entity*> points = std::vector<Entity*>();
    std::vector<Entity*> ais = std::vector<Entity*>();
    std::vector<Entity*> players = std::vector<Entity*>();
    std::vector<Entity*> big_points = std::vector<Entity*>();
};


#endif //PACMAN_GAMEPLAYSYSTEM_H

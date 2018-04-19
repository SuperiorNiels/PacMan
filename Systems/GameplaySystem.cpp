//
// Created by niels on 19.04.18.
//

#include "GameplaySystem.h"

GameplaySystem::GameplaySystem()
{
    component_types = {COLLISION_COMPONENT}; // not all entities with collision component will be added to this system
}

void GameplaySystem::addEntity(Entity *e)
{
    if(e->hasComponentType(AI_COMPONENT))
        ais.push_back(e);
    if(e->hasComponentType(PLAYER_INPUT_COMPONENT))
        players.push_back(e);
    if(e->hasComponentType(POINTS_COMPONENT))
        points.push_back(e);
}

bool GameplaySystem::entityInSystem(entityID id)
{
    std::vector<std::vector<Entity*>*> to_check = std::vector<std::vector<Entity*>*>();
    to_check.push_back(&ais);
    to_check.push_back(&players);
    to_check.push_back(&points);
    to_check.push_back(&big_points);
    for(auto& vector : to_check)
    {
        for(auto& e : *vector)
        {
            if(e->id == id)
                return true;
        }
    }
    return false;
}

void GameplaySystem::removeEntity(entityID id)
{
    std::vector<std::vector<Entity*>*> to_check = std::vector<std::vector<Entity*>*>();
    to_check.push_back(&ais);
    to_check.push_back(&players);
    to_check.push_back(&points);
    to_check.push_back(&big_points);
    for(auto& vector : to_check)
    {
        for(auto it = vector->begin(); it != vector->end(); it++)
        {
            Entity* e = it.operator*();
            if(e->id == id)
            {
                vector->erase(it);
                return;
            }
        }
    }
}

void GameplaySystem::update()
{
    for(auto& e : entities) {
        std::cout << "Hello" << std::endl;
    }
}
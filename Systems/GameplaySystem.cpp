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
    if(!entityInSystem(e->id))
    {
        if(e->hasComponentType(AI_COMPONENT))
            ais.push_back(e);
        if(e->hasComponentType(PLAYER_INPUT_COMPONENT))
            players.push_back(e);
        if(e->hasComponentType(POINTS_COMPONENT))
            points.push_back(e);
        System::addEntity(e);
    }
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
    System::removeEntity(id);
}

void GameplaySystem::update()
{
    auto* score = players[0]->getComponentByType<ScoreComponent>(SCORE_COMPONENT);
    auto* lives = players[0]->getComponentByType<LivesComponent>(LIVES_COMPONENT);

    if(lives->lives == 0)
        std::cout << "Game Over!" << std::endl;
    if(points.empty())
        std::cout << "You Win!" << std::endl;
}
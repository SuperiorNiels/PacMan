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
    for(auto& ai : ais)
    {
        auto* mc = ai->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
        if(mc->state == IDLE)
        {
            auto* ac = ai->getComponentByType<AIComponent>(AI_COMPONENT);
            auto* player_pos = players[0]->getComponentByType<PositionComponent>(POSITION_COMPONENT);
            switch(ac->state)
            {
                case HOME:
                    if(ac->score_before_leave < score->score)
                    {
                        ac->timer->startTimer();
                        ac->state = SCATTER;
                        break;
                    }
                case SCATTER:
                    ac->target_x = ac->scatter_x;
                    ac->target_y = ac->scatter_y;
                    if(ac->timer->getTime() > ac->time_to_wait)
                    {
                        ac->timer->resetTimer();
                        ac->timer->startTimer();
                        ac->time_to_wait = 20000;
                        ac->state = CHASE;
                    }
                    break;
                case CHASE:
                    ac->target_x = player_pos->x;
                    ac->target_y = player_pos->y;
                    if(ac->timer->getTime() > ac->time_to_wait)
                    {
                        ac->timer->resetTimer();
                        ac->timer->startTimer();
                        ac->time_to_wait = 7000;
                    }
                    break;
                case FLEE:
                    break;
                default:
                    break;
            }

        }
    }
    if(points.empty())
        std::cout << "You Win!" << std::endl;
}
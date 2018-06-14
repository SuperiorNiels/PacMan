//
// Created by niels on 07/03/18.
//

#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
    component_types = {COLLISION_COMPONENT};
}

void CollisionSystem::addEntity(Entity *e)
{
    if(e->hasComponentType(PLAYER_INPUT_COMPONENT) && !entityInSystem(e->id))
    {
        players[e->id] = e;
        return;
    }
    if(e->hasComponentType(AI_COMPONENT) && !entityInSystem(e->id))
    {
        ghosts[e->id] = e;
        return;
    }
    System::addEntity(e);
}

void CollisionSystem::removeEntity(entityID id)
{
    if(players.find(id) != players.end())
    {
        auto it = players.find(id);
        players.erase(it);
        return;
    }
    if(ghosts.find(id) != ghosts.end())
    {
        auto it = ghosts.find(id);
        ghosts.erase(it);
        return;
    }
    System::removeEntity(id);
}

bool CollisionSystem::entityInSystem(entityID id)
{
    if(players.find(id) != players.end())
        return true;
    if(ghosts.find(id) != ghosts.end())
        return true;
    return System::entityInSystem(id);
}

void CollisionSystem::update()
{
    for(auto p_it : players)
    {
        auto* player = p_it.second;
        auto* mc = player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
        auto* pc = player->getComponentByType<PositionComponent>(POSITION_COMPONENT);

        double wanted_x = pc->x + movement_vector[mc->wanted_dir][0];
        double wanted_y = pc->y + movement_vector[mc->wanted_dir][1];
        double new_x = pc->x + movement_vector[mc->current_dir][0];
        double new_y = pc->y + movement_vector[mc->current_dir][1];

        bool wanted_possible = true;
        bool current_possible = true;

        std::vector<Entity *> to_remove = std::vector<Entity *>();

        for (auto it : entities) {
            auto entity = it.second; // get entity
            auto *pc2 = entity->getComponentByType<PositionComponent>(POSITION_COMPONENT);
            if (!(entity->hasComponentType(POINTS_COMPONENT) || entity->hasComponentType(ENERGIZER_COMPONENT))) {
                if (wanted_x == pc2->x && wanted_y == pc2->y)
                    wanted_possible = false;

                if (new_x == pc2->x && new_y == pc2->y)
                    current_possible = false;
            } else {
                if (pc->x == pc2->x && pc->y == pc2->y) {
                    if (player->hasComponentType(SCORE_COMPONENT) && entity->hasComponentType(POINTS_COMPONENT)) {
                        auto *sc = player->getComponentByType<ScoreComponent>(SCORE_COMPONENT);
                        auto *pp = entity->getComponentByType<PointsComponent>(POINTS_COMPONENT);
                        sc->score += pp->points;
                    }
                    if (player->hasComponentType(SCORE_COMPONENT) && entity->hasComponentType(ENERGIZER_COMPONENT)) {
                        auto *sc = player->getComponentByType<ScoreComponent>(SCORE_COMPONENT);
                        auto *ec = entity->getComponentByType<EnergizerComponent>(ENERGIZER_COMPONENT);
                        sc->score += ec->points;
                        for (auto g_it : ghosts) {
                            auto *ghost = g_it.second;
                            auto *ac = ghost->getComponentByType<AIComponent>(AI_COMPONENT);
                            if (ac->state != HOME) {
                                ac->state = FLEE;
                                ac->timer->resetTimer();
                                ac->timer->startTimer();
                                ac->time_to_wait = 2500; // 2.5 seconds in flee state
                            }
                        }
                    }
                    to_remove.push_back(entity);
                }
            }
        }

        for (auto *e : to_remove) {
            e->clearComponents();
            removeEntity(e->id);
        }

        if (wanted_possible)
            mc->current_dir = mc->wanted_dir;
        if (!wanted_possible && !current_possible) {
            mc->wanted_dir = STOP;
            mc->current_dir = STOP;
        }

        for (auto& it : ghosts)
        {
            auto* ghost = it.second;

            auto *ac = ghost->getComponentByType<AIComponent>(AI_COMPONENT);
            if (ac->state != RETURN) {
                auto *pc2 = ghost->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                if (pc->x == pc2->x && pc->y == (pc2->y)) {
                    if (ac->state == FLEE) {
                        if (player->hasComponentType(SCORE_COMPONENT) && ghost->hasComponentType(POINTS_COMPONENT)) {
                            auto *sc = player->getComponentByType<ScoreComponent>(SCORE_COMPONENT);
                            auto *pp = ghost->getComponentByType<PointsComponent>(POINTS_COMPONENT);
                            sc->score += pp->points;
                        }
                        struct timespec tim1{}, tim2{};
                        tim1.tv_sec = 0;
                        tim1.tv_nsec = 500000000L;
                        nanosleep(&tim1, &tim2);
                        ac->state = RETURN;
                    } else {
                        mc->wanted_dir = STOP;
                        mc->current_dir = STOP;
                        if (player->hasComponentType(LIVES_COMPONENT)) {
                            auto *lc = player->getComponentByType<LivesComponent>(LIVES_COMPONENT);
                            lc->lives--;
                            pc->x = lc->start_x;
                            pc->y = lc->start_y;
                        }
                    }
                }
            }
        }
    }
}
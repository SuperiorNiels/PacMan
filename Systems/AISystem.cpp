//
// Created by niels on 06/03/18.
//

#include "AISystem.h"

AISystem::AISystem(World* world)
{
    component_types = {AI_COMPONENT};
    AISystem::world = world;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    gen = std::mt19937(rd()); //Standard mersenne_twister_engine seeded with rd()
    dis = std::uniform_int_distribution<>(0, 50);
}

void AISystem::update()
{
    for (auto it : entities)
    {
        auto e = it.second; // get entity
        if(e->hasComponentTypes({AI_COMPONENT,MOVABLE_COMPONENT,POSITION_COMPONENT}))
        {
            auto *mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            if (mc->state == IDLE)
            {
                updateState(e);

                auto *ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
                auto *pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);

                std::multimap<double, direction> best_dirs = std::multimap<double, direction>();

                for(int i=1; i<5; i++)
                {
                    int new_x = pc->x + movement_vector[i][0];
                    int new_y = pc->y + movement_vector[i][1];
                    if(world->getWorld()[new_y][new_x] != 1)
                    {
                        if(world->getWorld()[new_y][new_x] == 2 && !(ac->state == HOME || ac->state == LEAVE || ac->state == RETURN))
                            continue;

                        // Direction is possible
                        double distance = calculateDistance(new_x, new_y, ac->target_x, ac->target_y);

                        direction wanted_dir = STOP;
                        if(i == 1)
                            wanted_dir = LEFT;
                        else if(i == 2)
                            wanted_dir = RIGHT;
                        else if(i == 3)
                            wanted_dir = UP;
                        else if(i == 4)
                            wanted_dir = DOWN;

                        best_dirs.emplace(distance, wanted_dir);
                    }
                }

                for (auto &best_dir : best_dirs)
                {
                    bool change = false;
                    switch(best_dir.second)
                    {
                        case LEFT:
                            if(ac->previous != RIGHT)
                                change = true;
                            break;
                        case RIGHT:
                            if(ac->previous != LEFT)
                                change = true;
                            break;
                        case UP:
                            if(ac->previous != DOWN)
                                change = true;
                            break;
                        case DOWN:
                            if(ac->previous != UP)
                                change = true;
                            break;
                        default:
                            break;
                    }

                    if(change)
                    {
                        mc->wanted_dir = best_dir.second;
                        mc->current_dir = best_dir.second;
                        ac->previous = best_dir.second;
                        break;
                    }
                }
            }
        }
    }
}

void AISystem::updateState(Entity* e)
{
    auto* ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
    auto* player_score = ac->player->getComponentByType<ScoreComponent>(SCORE_COMPONENT);
    auto* ai_pos = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
    switch(ac->state)
    {
        case RETURN:
            ac->target_x = ac->home_x;
            ac->target_y = ac->home_y;
            if(ai_pos->x == ac->home_x && ai_pos->y == ac->home_y)
            {
                ac->state = HOME;
            }
            break;
        case HOME:
            ac->target_x = ac->home_x;
            ac->target_y = ac->home_y;
            if(ac->score_before_leave <= player_score->score && ai_pos->x == ac->home_x && ai_pos->y == ac->home_y)
            {
                ac->timer->startTimer();
                ac->state = LEAVE;
            }
            break;
        case LEAVE:
            ac->target_x = ac->leave_x;
            ac->target_y = ac->leave_y;
            if(ai_pos->x == ac->leave_x && ai_pos->y == ac->leave_y)
            {
                ac->timer->startTimer();
                ac->state = SCATTER;
            }
            break;
        case SCATTER:
            ac->target_x = ac->scatter_x;
            ac->target_y = ac->scatter_y;
            if(ac->timer->getTime() > ac->time_to_wait)
            {
                ac->timer->resetTimer();
                ac->timer->startTimer();
                ac->time_to_wait = 8000;
                ac->state = CHASE;
            }
            break;
        case CHASE:
            if(ac->ai_type == RED)
                calculateRedTarget(e);
            else if(ac->ai_type == PINK)
                calculatePinkTarget(e);
            else if(ac->ai_type == ORANGE)
                calculateOrangeTarget(e);
            else if (ac->ai_type == BLUE)
                calculateBlueTarget(e);
            if(ac->timer->getTime() > ac->time_to_wait)
            {
                ac->timer->resetTimer();
                ac->timer->startTimer();
                ac->time_to_wait = 7000;
                ac->state = SCATTER;
            }
            break;
        case FLEE:
            ac->target_x = dis(gen);
            ac->target_y = dis(gen);
            if(ac->timer->getTime() > ac->time_to_wait)
            {
                ac->timer->resetTimer();
                ac->timer->startTimer();
                ac->time_to_wait = 3000;
                ac->state = SCATTER;
            }
            break;
        default:
            break;
    }
}

void AISystem::calculateRedTarget(Entity *e)
{
    auto* ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
    auto* player_pos = ac->player->getComponentByType<PositionComponent>(POSITION_COMPONENT);
    ac->target_x = player_pos->x;
    ac->target_y = player_pos->y;
}

void AISystem::calculatePinkTarget(Entity *e)
{
    auto* ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
    auto* player_pos = ac->player->getComponentByType<PositionComponent>(POSITION_COMPONENT);
    auto* player_mov = ac->player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);

    int new_x = player_pos->x;
    int new_y = player_pos->y;
    switch(player_mov->current_dir)
    {
        case LEFT:
            new_x -= 4;
            break;
        case RIGHT:
            new_x += 4;
            break;
        case UP:
            new_y -= 4;
            break;
        case DOWN:
            new_y += 4;
            break;
        default:
            break;
    }
    ac->target_x = new_x;
    ac->target_y = new_y;
}

void AISystem::calculateOrangeTarget(Entity *e)
{
    auto* pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
    auto* ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
    auto* player_pos = ac->player->getComponentByType<PositionComponent>(POSITION_COMPONENT);

    double distance = sqrt(calculateDistance(pc->x, pc->y, player_pos->x, player_pos->y));

    if(distance < 8.)
    {
        ac->target_x = ac->scatter_x;
        ac->target_y = ac->scatter_y;
        return;
    }

    ac->target_x = player_pos->x;
    ac->target_y = player_pos->y;
}

void AISystem::calculateBlueTarget(Entity *e)
{
    auto* pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
    auto* ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
    auto* player_pos = ac->player->getComponentByType<PositionComponent>(POSITION_COMPONENT);

    double distance = sqrt(calculateDistance(pc->x, pc->y, player_pos->x, player_pos->y));

    if(distance < 8.)
    {
        ac->target_x = ac->scatter_x;
        ac->target_y = ac->scatter_y;
        return;
    }

    auto* player_mov = ac->player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
    int new_x = player_pos->x;
    int new_y = player_pos->y;
    switch(player_mov->current_dir)
    {
        case LEFT:
            new_x -= 4;
            break;
        case RIGHT:
            new_x += 4;
            break;
        case UP:
            new_y -= 4;
            break;
        case DOWN:
            new_y += 4;
            break;
        default:
            break;
    }
    ac->target_x = new_x;
    ac->target_y = new_y;
}

double AISystem::calculateDistance(int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx*dx + dy*dy;
}
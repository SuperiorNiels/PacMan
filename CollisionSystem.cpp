//
// Created by niels on 07/03/18.
//

#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
    component_types = {COLLISION_COMPONENT};
}

void CollisionSystem::update()
{
    // Search for player entity
    Entity* player = nullptr;
    for(auto& e : entities)
    {
        if(e->getComponentByType<PlayerInputComponent>(PLAYER_INPUT_COMPONENT) != nullptr)
        {
            player = e;
            break;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);

    if(player != nullptr)
    {
        auto* p = player->getComponentByType<PositionComponent>(POSITION_COMPONENT);
        auto* rc = player->getComponentByType<RenderComponent>(RENDER_COMPONENT);
        SDL_Rect player_box = SDL_Rect();
        player_box.x = p->x;
        player_box.y = p->y;
        player_box.w = rc->width;
        player_box.h = rc->height;
        for(auto& e : entities)
        {
            if(e->id != player->id)
            {
                auto* p2 = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                auto* rc2 = e->getComponentByType<RenderComponent>(RENDER_COMPONENT);
                SDL_Rect entity_box = SDL_Rect();
                entity_box.x = p2->x;
                entity_box.y = p2->y;
                entity_box.w = rc2->width;
                entity_box.h = rc2->height;
                if(checkCollision(player_box,entity_box))
                {
                    //std::cout << "Player collided with entity: " << e->id << std::endl;
                    auto* m = player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
                    m->x_speed = 0;
                    m->y_speed = 0;
                }
            }
        }
    }
}

bool CollisionSystem::checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(renderer, &a);
    SDL_RenderDrawRect(renderer, &b);

    if( bottomA <= topB )
    {
        return false;
    }
    if( topA >= bottomB )
    {
        return false;
    }
    if( rightA <= leftB )
    {
        return false;
    }
    return leftA < rightB;
}
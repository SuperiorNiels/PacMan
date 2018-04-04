//
// Created by niels on 05/03/18.
//

#include "SDL_RenderSystem.h"

SDL_RenderSystem::SDL_RenderSystem(World* world, int screen_width, int screen_height, TimerSystem* timer) :
        RenderSystem(world,screen_width,screen_height,timer)
{
    component_types = {RENDER_COMPONENT};

    // Initialze SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL not initialized! Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        // Create the window
        window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  screen_width, screen_height, SDL_WINDOW_SHOWN);
        if(window == nullptr)
        {
            std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            // Initialize renderer vsync: | SDL_RENDERER_PRESENTVSYNC
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == nullptr)
            {
                std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
            }
            else
            {
                if(SDL_RenderSetScale(renderer,1,1) < 0)
                {
                    std::cout << "Error setting renderer scale. Error: " << SDL_GetError() << std::endl;
                }
                else
                {
                    // Initialize renderer color
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                    // Initialize image loader
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags))
                    {
                        std::cout << "SDL_image failed to initialize! Error: " << IMG_GetError() << std::endl;
                    }
                }
            }
        }
    }
}

void SDL_RenderSystem::update()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);

    for (auto &e : entities)
    {
        if (e->hasComponentTypes({POSITION_COMPONENT, RENDER_COMPONENT}))
        {
            auto *rc = e->getComponentByType<SDL_RenderComponent>(RENDER_COMPONENT);
            if (rc->visible)
            {
                SDL_Rect position = getPosition(e);

                if(e->hasComponentType(PLAYER_INPUT_COMPONENT))
                {
                    double x_offset = 0.3*tile_width;
                    double y_offset = 0.3*tile_width; // fixme: hardcoded values
                    position.x = (int) (position.x - x_offset);
                    position.y = (int) (position.y - y_offset);
                }

                SDL_Rect clip = getClip(e);

                position.w = (int) floor(clip.w * rc->scale);
                position.h = (int) floor(clip.h * rc->scale);

                renderCollisionBox(e);
                SDL_RenderCopy(renderer, rc->texture, &clip, &position);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

SDL_Rect SDL_RenderSystem::getPosition(Entity *e)
{
    SDL_Rect position = SDL_Rect();
    if(e->hasComponentType(POSITION_COMPONENT))
    {
        auto *p = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
        auto *rc = e->getComponentByType<RenderComponent>(RENDER_COMPONENT);

        auto x = (int) floor(p->x * tile_width);
        auto y = (int) floor(p->y * tile_width);

        if(e->hasComponentType(MOVABLE_COMPONENT))
        {
            auto* mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            if(mc->state == MOVING)
            {
                mc->time += timer->getTimerStep() / 1000.f;

                double t = mc->time / (1.f/mc->speed);

                if(t >= 1)
                {
                    mc->time = 0;
                    t = 1;
                    mc->state = IDLE;
                }

                if(p->x - mc->x_prev != 0)
                    x = (int) (mc->x_prev * tile_width + (p->x - mc->x_prev) * t * tile_width);
                if(p->y - mc->y_prev != 0)
                    y = (int) (mc->y_prev * tile_width + (p->y - mc->y_prev) * t * tile_width);
            }
        }

        position = {x, y, rc->width * tile_width / 8, rc->height * tile_width / 8}; // fixme
    }
    return position;
}

SDL_Rect SDL_RenderSystem::getClip(Entity *e)
{
    auto *rc = e->getComponentByType<SDL_RenderComponent>(RENDER_COMPONENT);
    SDL_Rect clip = SDL_Rect();
    if (!rc->clips.empty())
    {
        clip = *rc->clips[0];
        if (e->hasComponentType(MOVABLE_COMPONENT))
        {
            auto *m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            rc->frame_offset = rc->direction_offsets[m->current_dir-1];
            if (m->state != IDLE || m->current_dir != STOP)
                clip = *rc->clips[rc->current_frame + rc->frame_offset];
        }
        if (rc->count > rc->animation_speed)
        {
            rc->current_frame = (rc->current_frame + 1) % rc->animation_length;
            rc->count = 0;
        }

        rc->count++;
    }
    return clip;
}

void SDL_RenderSystem::renderCollisionBox(Entity *e)
{
    if(e->hasComponentType(POSITION_COMPONENT))
    {
        auto* cc = e->getComponentByType<CollisionComponent>(COLLISION_COMPONENT);
        SDL_Rect aa = getPosition(e);
        aa.x = aa.x + (int) floor(cc->collision_box.x);
        aa.y = aa.y + (int) floor(cc->collision_box.y);
        aa.w = (int) floor(cc->collision_box.w) * tile_width;
        aa.h = (int) floor(cc->collision_box.h) * tile_width;
        if(e->hasComponentType(AI_COMPONENT))
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
            SDL_RenderDrawRect(renderer, &aa);
        }
        else if(e->hasComponentType(PLAYER_INPUT_COMPONENT))
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
            SDL_RenderFillRect(renderer, &aa);
        }
        else if(e->hasComponentType(POINTS_COMPONENT))
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xAB, 0x00, 0xFF);
            SDL_RenderDrawRect(renderer, &aa);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
            SDL_RenderDrawRect(renderer, &aa);
        }
    }
}

SDL_RenderSystem::~SDL_RenderSystem()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;
    IMG_Quit();
    SDL_Quit();
}
//
// Created by niels on 05/03/18.
//

#include "SDL_RenderSystem.h"

SDL_RenderSystem::SDL_RenderSystem(World* world, int screen_width, int screen_height) : RenderSystem(world,screen_width,screen_height)
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

    for(auto& e : entities)
    {
        if (e->hasComponentTypes({POSITION_COMPONENT,RENDER_COMPONENT}))
        {
            auto *rc = e->getComponentByType<SDL_RenderComponent>(RENDER_COMPONENT);
            auto *p = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
            if (rc->visible)
            {
                auto x = (int) floor(p->x * tile_width);
                auto y = (int) floor(p->y * tile_width);
                if(e->hasComponentType(PLAYER_INPUT_COMPONENT) || e->hasComponentType(AI_COMPONENT))
                {
                    x = (int) floor((p->x-(0.3*tile_width*(1.f/tile_width))) * tile_width);
                    y = (int) floor((p->y-(0.3*tile_width*(1.f/tile_width))) * tile_width);
                    //std::cout << "x: " << x << " y: " << y << std::endl;
                }
                // Create render position and render
                SDL_Rect position = {x, y, rc->width*tile_width/8, rc->height*tile_width/8};

                SDL_Rect *clip = nullptr;
                if (!rc->clips.empty())
                {
                    if (rc->count > rc->animation_speed)
                    {
                        rc->current_frame = (rc->current_frame + 1) % rc->animation_length;
                        rc->count = 0;
                    }
                    clip = rc->clips[rc->current_frame + rc->frame_offset];
                    if(e->hasComponentType(MOVABLE_COMPONENT))
                    {
                        auto *m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
                        if(m->current_dir == STOP)
                            clip = rc->clips[0];
                    }
                    position.w = (int)floor(clip->w*rc->scale);
                    position.h = (int)floor(clip->h*rc->scale);
                    rc->count++;
                }
                renderCollisionBox(e);
                SDL_RenderCopy(renderer, rc->texture, clip, &position);
                //std::cout << "[SDL_Render] Entity id: " << e->id << " rendered." << std::endl;
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void SDL_RenderSystem::renderCollisionBox(Entity *e)
{
    if(e->hasComponentType(COLLISION_COMPONENT) && e->hasComponentType(POSITION_COMPONENT))
    {
        auto* cc = e->getComponentByType<CollisionComponent>(COLLISION_COMPONENT);
        auto* pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
        SDL_Rect aa = SDL_Rect();
        aa.x = (int) floor(pc->x * tile_width) + cc->collision_box.x;
        aa.y = (int) floor(pc->y * tile_width) + cc->collision_box.y;
        aa.w = cc->collision_box.w;
        aa.h = cc->collision_box.h;
        if(e->hasComponentType(AI_COMPONENT))
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
            SDL_RenderDrawRect(renderer, &aa);
        }
        else if(e->hasComponentType(MOVABLE_COMPONENT))
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
            SDL_RenderDrawRect(renderer, &aa);
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
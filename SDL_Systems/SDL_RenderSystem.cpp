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
            auto *m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            if (rc->visible)
            {
                // Create render position and render
                SDL_Rect position = {(int) floor(p->x * tile_width), (int) floor(p->y * tile_width), rc->width*tile_width/8,
                                     rc->height*tile_width/8};

                SDL_Rect *clip = nullptr;
                if (!rc->clips.empty())
                {
                    if (m != nullptr)
                    {
                        if (m->x_speed != 0 || m->y_speed != 0)
                        {
                            // Entity is moving, animate
                            if (rc->count > rc->animation_speed)
                            {
                                rc->current_frame = (rc->current_frame + 1) % rc->animation_length;
                                rc->count = 0;
                            }
                            clip = rc->clips[rc->current_frame + rc->frame_offset];
                        }
                        else
                        {
                            clip = rc->clips[0]; // still image should be at this position
                        }
                    }
                    else
                    {
                        if (rc->count > rc->animation_speed)
                        {
                            rc->current_frame = (rc->current_frame + 1) % rc->animation_length;
                            rc->count = 0;
                        }
                        clip = rc->clips[rc->current_frame + rc->frame_offset];
                    }
                    position.w = (int)floor(clip->w*rc->scale);
                    position.h = (int)floor(clip->h*rc->scale);
                    rc->count++;
                }
                renderCollisionBox(e);
                //SDL_RenderCopy(renderer, rc->texture, clip, &position);
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
        if(e->hasComponentType(AI_COMPONENT))
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
        }
        else if(e->hasComponentType(MOVABLE_COMPONENT))
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
        }
        else if(e->hasComponentType(POINTS_COMPONENT))
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xAB, 0x00, 0xFF);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
        }
        SDL_Rect aa = SDL_Rect();
        aa.x = (int) floor(pc->x * tile_width) + cc->collision_box[0];
        aa.y = (int) floor(pc->y * tile_width) + cc->collision_box[1];
        aa.w = cc->collision_box[2];
        aa.h = cc->collision_box[3];

        SDL_RenderDrawRect(renderer, &aa);
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
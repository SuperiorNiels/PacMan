//
// Created by niels on 05/03/18.
//

#include "SDL_RenderSystem.h"

SDL_RenderSystem::SDL_RenderSystem()
{
    component_types = {0, 10}; // position component, sdl_rendercomponent

    // Initialze SDL
    // TODO: remove hardcoded variables
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL not initialized! Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        // Create the window
        window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  600, 600, SDL_WINDOW_SHOWN);
        if(window == nullptr)
        {
            std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            // Initialize renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == nullptr)
            {
                std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
            }
            else
            {
                if(SDL_RenderSetScale(renderer,1, 1) < 0)
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
        auto* rc = e->getComponentByType<SDL_RenderComponent>(10);
        auto* p = e->getComponentByType<PositionComponent>(0);
        // Create render position and render
        SDL_Rect position = {p->x, p->y, rc->width, rc->height};

        if(rc->clips.size() != 0)
        {
            // TODO: add clip rendering
        }

        SDL_RenderCopy(renderer, rc->texture, nullptr, &position);
        std::cout << "[SDL_Render] Entity id: " << e->id << " rendered." << std::endl;
    }

    SDL_RenderPresent(renderer);
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
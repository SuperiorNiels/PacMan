//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_COMPONENTS_H
#define ECS_SDL_COMPONENTS_H

#include "ECS/ECS.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class SDL_RenderComponent : public Component
{
public:
    SDL_RenderComponent() { type = 10; }
    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;
    SDL_Rect* clip = nullptr;
    int current_frame = 0;
    ~SDL_RenderComponent() override
    {
        SDL_DestroyTexture(texture);
        delete clip;
    };
};

// TODO: add sdl input component

#endif //ECS_SDL_COMPONENTS_H

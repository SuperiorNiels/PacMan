//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_COMPONENTS_H
#define ECS_SDL_COMPONENTS_H

#include "ECS/Component.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class SDL_RenderComponent : public Component
{
public:
    SDL_RenderComponent() { type = 10; }
    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;
    std::vector<SDL_Rect*> clips = std::vector<SDL_Rect*>();
    int current_frame = 0;
};

// TODO: add sdl input component

#endif //ECS_SDL_COMPONENTS_H

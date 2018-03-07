//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_COMPONENTS_H
#define ECS_SDL_COMPONENTS_H

#include "ECS/ECS.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "PacMan_Components.h"

class SDL_RenderComponent : public RenderComponent
{
public:
    SDL_Texture* texture = nullptr;
    std::vector<SDL_Rect*> clips = std::vector<SDL_Rect*>();
    ~SDL_RenderComponent() override
    {
        SDL_DestroyTexture(texture);
        for(auto& c : clips)
            delete c;
    };
};

#endif //ECS_SDL_COMPONENTS_H

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
    std::vector<SDL_Rect*> clips = std::vector<SDL_Rect*>();
    int animation_length = 0;
    int animation_speed = 10;
    int current_frame = 0;
    int count = 0;
    int frame_offset = 0;
    int direction_offsets[4] = {0,0,0,0}; // left,right,up,down
    ~SDL_RenderComponent() override
    {
        SDL_DestroyTexture(texture);
        for(auto& c : clips)
            delete c;
    };
};

// TODO: add sdl input component

#endif //ECS_SDL_COMPONENTS_H

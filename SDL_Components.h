//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_COMPONENTS_H
#define ECS_SDL_COMPONENTS_H

#include "ECS/ECS.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "PacMan_Components.h"
#include "SDL_Text.h"

class SDL_RenderComponent : public RenderComponent
{
public:
    SDL_Texture* texture = nullptr; // Textures get destroyed by the factory!
    std::vector<SDL_Rect*> clips = std::vector<SDL_Rect*>();
    ~SDL_RenderComponent() override
    {
        for(auto& c : clips)
            delete c;
    };
};

class SDL_ScoreComponent : public ScoreComponent
{
public:
    SDL_Text* texture = nullptr;
};

class SDL_LivesComponent : public LivesComponent
{
public:
    SDL_Text* texture = nullptr;
};

class SDL_TextComponent : public TextComponent
{
public:
    SDL_Text* texture = nullptr;
};
#endif //ECS_SDL_COMPONENTS_H

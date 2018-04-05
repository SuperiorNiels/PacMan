//
// Created by niels on 05/04/18.
//

#ifndef PACMAN_SDL_TEXT_H
#define PACMAN_SDL_TEXT_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class SDL_Text
{
public:
    SDL_Text(std::string font, int size, SDL_Renderer* renderer);
    void setText(std::string text, SDL_Color color);
    SDL_Texture *getTexture() const;
    ~SDL_Text();
private:
    void free();
    TTF_Font* font = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
};


#endif //PACMAN_SDL_TEXT_H

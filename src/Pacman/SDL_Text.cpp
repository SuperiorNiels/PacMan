//
// Created by niels on 05/04/18.
//

#include "../../include/Pacman/SDL_Text.h"

namespace Pacman {

    SDL_Text::SDL_Text(std::string font, int size, SDL_Renderer *renderer) {
        SDL_Text::renderer = renderer;
        SDL_Text::font = TTF_OpenFont(font.c_str(), size);
        if (SDL_Text::font == nullptr)
            std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    void SDL_Text::setText(std::string text, SDL_Color color) {
        free();
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (textSurface == nullptr)
            std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        else {
            texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (texture == nullptr)
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            SDL_FreeSurface(textSurface);
        }
    }

    SDL_Texture *SDL_Text::getTexture() const {
        return texture;
    }

    void SDL_Text::free() {
        SDL_DestroyTexture(texture);
    }

    SDL_Text::~SDL_Text() {
        free();
        TTF_CloseFont(font);
    }

};

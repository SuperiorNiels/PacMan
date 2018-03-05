//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_FACTORY_H
#define ECS_SDL_FACTORY_H


#include <SDL2/SDL.h>
#include "AbstractFactory.h"

class SDL_Factory : public AbstractFactory {
public:
    Entity* createPacMan() override;
    System* createRenderSystem() override = 0;
private:
    SDL_Texture* createTexture();

};


#endif //ECS_SDL_FACTORY_H

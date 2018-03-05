//
// Created by niels on 05/03/18.
//

#include "SDL_Factory.h"
#include "SDL_Components.h"

Entity* SDL_Factory::createPacMan()
{
    // Create empty entity and add components
    auto* e = new Entity();
    auto* rc = new SDL_RenderComponent();
    rc->texture;
}

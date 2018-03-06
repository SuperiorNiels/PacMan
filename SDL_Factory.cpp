//
// Created by niels on 05/03/18.
//

#include "SDL_Factory.h"

#include <utility>
#include "SDL_Components.h"

Entity* SDL_Factory::createPacMan()
{
    // Create empty entity and add components
    auto* e = new Entity();
    e->addComponent(new PositionComponent());
    SDL_Rect rect = SDL_Rect();
    rect.x = 7;
    rect.y = 858;
    rect.w = 34;
    rect.h = 34;
    e->addComponent(createRenderComponent("../sprites.png"));
    return e;
}

Entity* SDL_Factory::createGhost()
{
    auto* e = new Entity();
    auto* p = new PositionComponent();
    p->x = 200;
    p->y = 250;
    e->addComponent(p);
    e->addComponent(createRenderComponent("../sprites.png"));
    return e;
}

System* SDL_Factory::createRenderSystem()
{
    // Check if rendersystem already exists
    if(renderSystem == nullptr)
    {
        renderSystem = new SDL_RenderSystem();
    }
    return renderSystem;
}

SDL_RenderComponent* SDL_Factory::createRenderComponent(std::string path, std::vector<SDL_Rect*> clips)
{
    auto* to_return = new SDL_RenderComponent();
    SDL_Texture* newTexture = nullptr;
    // First load image in surface
    SDL_Surface* currentImage = IMG_Load(path.c_str());
    if(currentImage == nullptr)
    {
        std::cout << "Unable to load image! Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    else
    {
        SDL_SetColorKey(currentImage, SDL_TRUE, SDL_MapRGB(currentImage->format, 0, 0, 0));
        newTexture = SDL_CreateTextureFromSurface(renderSystem->renderer, currentImage);
        if(newTexture == nullptr)
        {
            std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;
            return nullptr;
        }
        else
        {
            to_return->width = currentImage->w;
            to_return->height = currentImage->h;
        }
    }
    // Remove the newSurface form memory
    to_return->texture = newTexture;
    SDL_FreeSurface(currentImage);
    to_return->clips = std::move(clips);
    return to_return;
}

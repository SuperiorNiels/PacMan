//
// Created by niels on 05/03/18.
//

#include "SDL_Factory.h"

#include <utility>
#include "SDL_Components.h"

Entity* SDL_Factory::createPacMan(int x, int y)
{
    // Create empty entity and add components
    auto* e = new Entity();
    auto* p = new PositionComponent();
    p->x = x;
    p->y = y;
    e->addComponent(p);

    std::vector<SDL_Rect*> clips = std::vector<SDL_Rect*>();
    for(int i = 0; i < 12 ; i++)
    {
        auto* rect1 = new SDL_Rect();
        rect1->x = 858;
        rect1->y = 7+(i*50);
        rect1->w = 34;
        rect1->h = 34;
        clips.push_back(rect1);
    }
    auto* rc = createRenderComponent("../sprites.png",clips);
    rc->animation_length = 3;
    rc->animation_speed = 4;
    rc->direction_offsets[0] = 6;
    rc->direction_offsets[1] = 0;
    rc->direction_offsets[2] = 9;
    rc->direction_offsets[3] = 3;
    e->addComponent(rc);
    e->addComponent(new MovableComponent());
    return e;
}

Entity* SDL_Factory::createGhost(int x, int y)
{
    // Create empty entity and add components
    auto* e = new Entity();
    auto* p = new PositionComponent();
    p->x = x;
    p->y = y;
    e->addComponent(p);

    std::vector<SDL_Rect*> clips = std::vector<SDL_Rect*>();
    for(int i = 0; i < 8 ; i++)
    {
        auto* rect1 = new SDL_Rect();
        rect1->x = 5;
        rect1->y = 6+(i*50);
        rect1->w = 37;
        rect1->h = 34;
        clips.push_back(rect1);
    }
    auto* rc = createRenderComponent("../sprites.png",clips);
    rc->animation_length = 2;
    rc->animation_speed = 4;
    rc->direction_offsets[0] = 4;
    rc->direction_offsets[1] = 0;
    rc->direction_offsets[2] = 6;
    rc->direction_offsets[3] = 2;
    e->addComponent(rc);
    e->addComponent(new MovableComponent());
    e->addComponent(new AIComponent());
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

EventSystem* SDL_Factory::createEventSystem()
{
    return new SDL_EventSystem();
}

SDL_RenderComponent* SDL_Factory::createRenderComponent(std::string path, std::vector<SDL_Rect*> clips)
{
    auto* to_return = new SDL_RenderComponent();
    SDL_Texture *newTexture = nullptr;
    // Check if texture is already loaded in memory
    if(loadedTextures.find(path) == loadedTextures.end())
    {
        // First load image in surface
        SDL_Surface *currentImage = IMG_Load(path.c_str());
        if (currentImage == nullptr) {
            std::cout << "Unable to load image! Error: " << SDL_GetError() << std::endl;
            return nullptr;
        } else {
            SDL_SetColorKey(currentImage, SDL_TRUE, SDL_MapRGB(currentImage->format, 0, 0, 0));
            newTexture = SDL_CreateTextureFromSurface(renderSystem->renderer, currentImage);
            if (newTexture == nullptr) {
                std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;
                return nullptr;
            }
        }
        SDL_FreeSurface(currentImage);
        loadedTextures[path] = newTexture;
    }
    else
    {
        // Texture is already in memory
        newTexture = loadedTextures[path];
    }

    SDL_QueryTexture(newTexture, nullptr, nullptr, &to_return->width, &to_return->height);

    to_return->texture = newTexture;
    to_return->clips = std::move(clips);
    return to_return;
}

SDL_Factory::~SDL_Factory()
{
    delete renderSystem;
}
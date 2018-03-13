//
// Created by niels on 05/03/18.
//

#include "SDL_Factory.h"
#include "Systems/CollisionSystem.h"

#include <fstream>

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
        rect1->x = pacman[i][0]; // 908
        rect1->y = pacman[i][1];
        rect1->w = pacman[i][2];
        rect1->h = pacman[i][3];
        clips.push_back(rect1);
    }
    auto* rc = createRenderComponent(sprites_sheet,clips);
    rc->animation_length = 3;
    rc->animation_speed = 4;
    rc->direction_offsets[0] = 3;
    rc->direction_offsets[1] = 0;
    rc->direction_offsets[2] = 6;
    rc->direction_offsets[3] = 9;
    e->addComponent(rc);
    auto *cc = new CollisionComponent();
    cc->collision_box[0] = 2;
    cc->collision_box[1] = 2;
    cc->collision_box[2] = 8;
    cc->collision_box[3] = 8;
    e->addComponent(cc);
    e->addComponent(new MovableComponent());
    e->addComponent(new PlayerInputComponent());
    return e;
}

Entity* SDL_Factory::createGhost(int x, int y, ghost_color color)
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
        rect1->x = ghost[i][0];
        rect1->y = ghost[i][1]+(16*(color%4));
        rect1->w = ghost[i][2];
        rect1->h = ghost[i][3];
        clips.push_back(rect1);
    }
    auto* rc = createRenderComponent(sprites_sheet,clips);
    rc->animation_length = 2;
    rc->animation_speed = 4;
    rc->direction_offsets[0] = 2;
    rc->direction_offsets[1] = 0;
    rc->direction_offsets[2] = 4;
    rc->direction_offsets[3] = 6;
    e->addComponent(rc);
    auto *cc = new CollisionComponent();
    cc->collision_box[0] = 2;
    cc->collision_box[1] = 2;
    cc->collision_box[2] = 8;
    cc->collision_box[3] = 8;
    e->addComponent(cc);
    e->addComponent(new MovableComponent());
    e->addComponent(new AIComponent());
    e->addComponent(new CollisionComponent());
    return e;
}

std::vector<Entity*> SDL_Factory::createWorld()
{
    std::ifstream in(collision_map);
    std::vector<Entity*> world;

    int wall_types[28][31];
    for(int x=0;x<31;x++)
    {
        for (auto &wall_type : wall_types) {
            in >> wall_type[x];
        }
    }

    for(int x=0;x<28;x++)
    {
        for(int y=0;y<31;y++)
        {
            auto* e = new Entity();
            auto* p = new PositionComponent();
            p->x = x * 8;
            p->y = y * 8;
            auto *rect = new SDL_Rect();
            rect->x = p->x;
            rect->y = p->y;
            rect->w = 8;
            rect->h = 8;
            std::vector<SDL_Rect*> clips;
            clips.push_back(rect);
            if(wall_types[x][y] == 1)
            {
                auto *cc = new CollisionComponent();
                cc->collision_box[0] = 0;
                cc->collision_box[1] = 0;
                cc->collision_box[2] = 8;
                cc->collision_box[3] = 8;
                e->addComponent(cc);
            }
            else if(wall_types[x][y] == 3)
            {
                auto *cc = new CollisionComponent();
                cc->collision_box[0] = 3;
                cc->collision_box[1] = 3;
                cc->collision_box[2] = 2;
                cc->collision_box[3] = 2;
                e->addComponent(cc);
                e->addComponent(new PointsComponent());
            }
            auto* rc = createRenderComponent(sprites_sheet,clips);
            e->addComponent(p);
            e->addComponent(rc);
            world.push_back(e);
        }
    }
    return world;
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

TimerSystem* SDL_Factory::createTimerSystem(int fps)
{
    return new SDL_TimerSystem(fps);
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

    if(clips.empty())
        SDL_QueryTexture(newTexture, nullptr, nullptr, &to_return->width, &to_return->height);
    else
    {
        to_return->width = clips[0]->w;
        to_return->height = clips[0]->h;
    }
    to_return->texture = newTexture;
    to_return->clips = std::move(clips);
    return to_return;
}

SDL_Factory::~SDL_Factory()
{
    delete renderSystem;
}
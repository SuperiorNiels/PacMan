//
// Created by niels on 05/03/18.
//

#include "SDL_Factory.h"

Entity* SDL_Factory::createPacMan(int x, int y)
{
    int tile_width = renderSystem->getTile_width();
    // Create empty entity and add components
    auto* e = new Entity();
    auto* pc = new PositionComponent();
    pc->x = x;
    pc->y = y;
    std::vector<SDL_Rect*> clips = std::vector<SDL_Rect*>();
    for (auto &i : pacman) {
        auto* rect1 = new SDL_Rect();
        rect1->x = i[0]; // 908
        rect1->y = i[1];
        rect1->w = i[2];
        rect1->h = i[3];
        clips.push_back(rect1);
    }
    auto* rc = createRenderComponent(sprites_sheet,clips);
    rc->animation_length = 3;
    rc->animation_speed = 4;
    rc->direction_offsets[0] = 3;
    rc->direction_offsets[1] = 0;
    rc->direction_offsets[2] = 6;
    rc->direction_offsets[3] = 9;
    rc->scale = tile_width/8;
    auto *cc = new CollisionComponent();
    cc->collision_box[0] = 0;
    cc->collision_box[1] = 0;
    cc->collision_box[2] = tile_width;
    cc->collision_box[3] = tile_width;
    e->addComponent(pc);
    e->addComponent(cc);
    e->addComponent(rc);
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
    for (auto &i : ghost) {
        auto* rect1 = new SDL_Rect();
        rect1->x = i[0];
        rect1->y = i[1]+(16*(color%4));
        rect1->w = i[2];
        rect1->h = i[3];
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

std::vector<Entity*> SDL_Factory::createWorld(World* world)
{
    std::vector<Entity*> entities = std::vector<Entity*>();
    int **map = world->getWorld();
    int tile_width = renderSystem->getTile_width();
    for(int x=0;x<world->getWidth();x++)
    {
        for(int y=0;y<world->getHeight();y++)
        {
            //std::cout << map[y][x] << " ";
            if(map[y][x] == 1)
            {
                auto *entity = new Entity();
                auto* pc = new PositionComponent();
                pc->x = x;
                pc->y = y;
                std::vector<SDL_Rect*> clips;
                SDL_Rect* rect = new SDL_Rect();
                // TODO : do not hardcode tile width on sprites sheet
                rect->x = x * 8;
                rect->y = y * 8;
                rect->w = 8;
                rect->h = 8;
                clips.push_back(rect);
                auto *cc = new CollisionComponent();
                cc->collision_box[0] = 0;
                cc->collision_box[1] = 0;
                cc->collision_box[2] = tile_width;
                cc->collision_box[3] = tile_width;
                auto* rc = createRenderComponent(sprites_sheet,clips);
                rc->scale = tile_width/8;
                entity->addComponent(rc);
                entity->addComponent(pc);
                entity->addComponent(cc);
                entities.push_back(entity);
            }
            else if(map[y][x] == 3)
            {
                auto *entity = new Entity();
                auto* pc = new PositionComponent();
                pc->x = x;
                pc->y = y;
                std::vector<SDL_Rect*> clips;
                SDL_Rect* rect = new SDL_Rect();
                // TODO : do not hardcode tile width on sprites sheet
                rect->x = x * 8;
                rect->y = y * 8;
                rect->w = 8;
                rect->h = 8;
                clips.push_back(rect);
                auto *cc = new CollisionComponent();
                cc->collision_box[0] = 0;
                cc->collision_box[1] = 0;
                cc->collision_box[2] = tile_width;
                cc->collision_box[3] = tile_width;
                auto* rc = createRenderComponent(sprites_sheet,clips);
                rc->scale = tile_width/8;
                entity->addComponent(rc);
                entity->addComponent(pc);
                entity->addComponent(cc);
                entity->addComponent(new PointsComponent());
                entities.push_back(entity);
            }
        }
        //std::cout << std::endl;
    }
    return entities;
}

RenderSystem* SDL_Factory::createRenderSystem(World* world, int screen_width, int screen_height)
{
    // Check if render system already exists
    if(renderSystem == nullptr)
    {
        renderSystem = new SDL_RenderSystem(world,screen_width,screen_height);
    }
    return renderSystem;
}

EventSystem* SDL_Factory::createEventSystem(double speed)
{
    return new SDL_EventSystem(speed);
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
    loadedTextures.clear();
}

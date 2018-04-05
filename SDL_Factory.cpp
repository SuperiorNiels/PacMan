//
// Created by niels on 05/03/18.
//

#include "SDL_Factory.h"

std::vector<Entity*> SDL_Factory::createWorldEntities(World *world)
{
    std::vector<Entity*> entities = std::vector<Entity*>();
    int **map = world->getWorld();
    int tile_width = renderSystem->getTile_width();
    for(int x=0;x<world->getWidth();x++)
    {
        for(int y=0;y<world->getHeight();y++)
        {
            //std::cout << map[y][x] << " ";
            Entity* entity = nullptr;
            if(map[y][x] == 1)
            {
                entity = config->createEntity("wall_tile",tile_width, x, y);
            }
            else if(map[y][x] == 3 || map[y][x] == 4)
            {
                entity = config->createEntity("point",tile_width, x, y);
            }
            if(entity != nullptr)
                entities.push_back(entity);
        }
        //std::cout << std::endl;
    }
    int i = 0;
    for(int x=0;x<world->getWidth();x++)
    {
        for (int y = 0; y < world->getHeight(); y++)
        {
            if(map[y][x] == 5)
                entities.push_back(config->createEntity("player",renderSystem->getTile_width(),x,y));
            if(map[y][x] == 6)
            {
                entities.push_back(config->createEntity("ghost",renderSystem->getTile_width(),x,y,0,i));
                i++;
            }
        }
    }
    return entities;
}

RenderSystem* SDL_Factory::createRenderSystem(World* world, int screen_width, int screen_height, TimerSystem* timer)
{
    // Check if render system already exists
    auto* res = new SDL_RenderSystem(world,screen_width,screen_height,timer);
    clearTextures();
    renderSystem = res;
    return res;
}

EventSystem* SDL_Factory::createEventSystem()
{
    return new SDL_EventSystem();
}

TimerSystem* SDL_Factory::createTimerSystem(int fps)
{
    return new SDL_TimerSystem(fps);
}

RenderComponent* SDL_Factory::createRenderComponent(std::string path, std::vector<clip> clips)
{
    auto* to_return = new SDL_RenderComponent();
    SDL_Texture *newTexture = nullptr;
    // Check if texture is already loaded in memory
    if(loadedTextures.find(path) == loadedTextures.end())
    {
        // First load image in surface
        SDL_Surface *currentImage = IMG_Load(path.c_str());
        if (currentImage == nullptr)
        {
            std::cout << "Unable to load image! Error: " << SDL_GetError() << std::endl;
            return nullptr;
        } else {
            SDL_SetColorKey(currentImage, SDL_TRUE, SDL_MapRGB(currentImage->format, 0, 0, 0));
            newTexture = SDL_CreateTextureFromSurface(renderSystem->renderer, currentImage);
            if (newTexture == nullptr)
            {
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
        SDL_QueryTexture(newTexture, nullptr, nullptr, 0, 0); //fixme

    to_return->texture = newTexture;

    std::vector<SDL_Rect*> sdl_clips = std::vector<SDL_Rect*>();
    for(auto clip : clips)
    {
        SDL_Rect* rect = new SDL_Rect();
        rect->x = clip.x;
        rect->y = clip.y;
        rect->w = clip.w;
        rect->h = clip.h;
        sdl_clips.push_back(rect);
    }
    to_return->clips = std::move(sdl_clips);

    return to_return;
}

ScoreComponent* SDL_Factory::createScoreComponent(std::string font, int font_size)
{
    auto* sc = new SDL_ScoreComponent();
    sc->texture = new SDL_Text(font,font_size,renderSystem->renderer);
    return sc;
}

LivesComponent* SDL_Factory::createLivesComponent(std::string font, int font_size)
{
    auto* lc = new SDL_LivesComponent();
    lc->text = new SDL_Text(font,font_size,renderSystem->renderer);
    return lc;
}

void SDL_Factory::clearTextures()
{
    for(auto it = loadedTextures.begin(); it != loadedTextures.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    loadedTextures.clear();
}

SDL_Factory::~SDL_Factory()
{
    clearTextures();
}

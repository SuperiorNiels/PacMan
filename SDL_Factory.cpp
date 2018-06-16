//
// Created by niels on 05/03/18.
//

#include "SDL_Factory.h"

std::vector<Entity *> SDL_Factory::createWorldEntities(World *world) {
    std::vector<Entity *> entities = std::vector<Entity *>();

    int **map = world->getWorld();
    int tile_width = renderSystem->getTile_width();

    for (int x = 0; x < world->getWidth(); x++) {
        for (int y = 0; y < world->getHeight(); y++) {
            switch (map[y][x]) {
                case 1:
                    entities.push_back(config->createEntity("wall_tile", tile_width, x, y));
                    break;
                case 2:
                    entities.push_back(config->createEntity("player_only_wall", tile_width, x, y));
                    break;
                case 3:
                    entities.push_back(config->createEntity("point", tile_width, x, y));
                    break;
                case 4:
                    entities.push_back(config->createEntity("big_point", tile_width, x, y));
                    break;
                case 5:
                    entities.push_back(config->createEntity("player", tile_width, x, y));
                    break;
                case 6:
                    entities.push_back(config->createEntity("red_ghost", tile_width, x, y));
                    break;
                case 7:
                    entities.push_back(config->createEntity("blue_ghost", tile_width, x, y));
                    break;
                case 8:
                    entities.push_back(config->createEntity("pink_ghost", tile_width, x, y));
                    break;
                case 9:
                    entities.push_back(config->createEntity("orange_ghost", tile_width, x, y));
                    break;
                default:
                    break;
            }
        }
    }

    if (!entities.empty()) {
        Entity *player = nullptr;
        for (auto *e : entities) {
            if (e->hasComponentType(PLAYER_INPUT_COMPONENT))
                player = e;
        }

        if (player != nullptr) {
            for (auto *e : entities) {
                if (e->hasComponentType(AI_COMPONENT)) {
                    auto *ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
                    ac->player = player;
                }
            }
        }
    }

    return entities;
}

RenderSystem* SDL_Factory::createRenderSystem(World* world, int screen_width, int screen_height, TimerSystem* timer)
{
    auto* res = new SDL_RenderSystem(world,screen_width,screen_height,timer);
    clearTextures();
    renderSystem = res;
    return res;
}

EventSystem *SDL_Factory::createEventSystem(std::map<events_numbers, bool> *events) {
    return new SDL_EventSystem(events);
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
        auto * rect = new SDL_Rect();
        rect->x = clip.x;
        rect->y = clip.y;
        rect->w = clip.w;
        rect->h = clip.h;
        sdl_clips.push_back(rect);
    }
    to_return->clips = std::move(sdl_clips);

    return to_return;
}

ScoreComponent *SDL_Factory::createScoreComponent()
{
    auto* sc = new SDL_ScoreComponent();
    auto* color = new SDL_Color();
    color->r = 0xff; color->g = 0xff; color->b = 0xff; color->a = 0xff;
    sc->color = color;
    auto font_size = (int) std::round(renderSystem->getTile_width() * 1.3);
    sc->texture = new SDL_Text(font,font_size,renderSystem->renderer);
    return sc;
}

LivesComponent *SDL_Factory::createLivesComponent()
{
    auto* lc = new SDL_LivesComponent();
    auto* color = new SDL_Color();
    color->r = 0xff; color->g = 0xff; color->b = 0xff; color->a = 0xff;
    lc->color = color;
    auto font_size = (int) std::round(renderSystem->getTile_width() * 1.3);
    lc->texture = new SDL_Text(font,font_size,renderSystem->renderer);
    return lc;
}

TextComponent *SDL_Factory::createTextComponent()
{
    auto* lc = new SDL_TextComponent();
    auto* color = new SDL_Color();
    color->r = 0xff; color->g = 0xff; color->b = 0xff; color->a = 0xff;
    lc->color = color;
    auto font_size = (int) std::round(renderSystem->getTile_width() * 1.45);
    lc->texture = new SDL_Text(font,font_size,renderSystem->renderer);
    return lc;
}

void SDL_Factory::clearTextures()
{
    for (auto &loadedTexture : loadedTextures)
    {
        SDL_DestroyTexture(loadedTexture.second);
    }
    loadedTextures.clear();
}

SDL_Factory::~SDL_Factory()
{
    clearTextures();
}

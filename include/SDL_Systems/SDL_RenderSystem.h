//
// Created by niels on 05/03/18.
//

#ifndef ECS_SDL_RENDERSYSTEM_H
#define ECS_SDL_RENDERSYSTEM_H

#include <sstream>
#include "../Pacman/SDL_Components.h"
#include "../Pacman/PacMan_Components.h"
#include "../Pacman/World.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/TimerSystem.h"

using namespace Pacman;

namespace SDL_Systems
{
    class SDL_RenderSystem : public Systems::RenderSystem
    {
    public:
        SDL_RenderSystem(Pacman::World *world, int screen_width, int screen_height, Systems::TimerSystem *timer, std::map<events_numbers, bool> *events);

        void update() override;

        void addEntity(Entity *e) override;

        void removeEntity(entityID id) override;

        bool entityInSystem(entityID id) override;

        ~SDL_RenderSystem() override;

        SDL_Renderer *renderer = nullptr;

    private:
        void renderPlayerComponent(Entity *e);

        void renderText(Entity *e);

        SDL_Window *window = nullptr;

        SDL_Rect getPosition(Entity *e);

        SDL_Rect getClip(Entity *e);

        std::map<entityID, Entity *> foreground; // background = standard entity list
    };
};

#endif // ECS_SDL_RENDERSYSTEM_H

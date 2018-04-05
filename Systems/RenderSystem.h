//
// Created by niels on 13/03/18.
//

#ifndef PACMAN_RENDERSYSTEM_H
#define PACMAN_RENDERSYSTEM_H

#include <cmath>
#include "../ECS/ECS.h"
#include "../World.h"
#include "TimerSystem.h"

class RenderSystem : public System
{
public:
    RenderSystem() = default;
    RenderSystem(World* world, int screen_width, int screen_height, TimerSystem* timer)
    {
        RenderSystem::screen_width = screen_width;
        RenderSystem::screen_height = screen_height;
        RenderSystem::timer = timer;

        double number1 = screen_height/world->getHeight();
        double number2 = screen_width/world->getWidth();

        RenderSystem::tile_width = (int)floor(std::min<double>(number1,number2));

        RenderSystem::x_screen_offset = (int) floor((screen_width - world->getWidth() * tile_width) / 2.f);
        RenderSystem::y_screen_offset = (int) floor((screen_height - world->getHeight() * tile_width) / 2.f);
    };
    int getTile_width() const { return tile_width; };
protected:
    int tile_width = 0; // square : width = height
    int screen_width = 0;
    int screen_height = 0;
    int x_screen_offset = 0;
    int y_screen_offset = 0;
    TimerSystem* timer = nullptr;
};

#endif //PACMAN_RENDERSYSTEM_H

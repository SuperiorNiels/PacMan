//
// Created by niels on 13/03/18.
//

#ifndef PACMAN_RENDERSYSTEM_H
#define PACMAN_RENDERSYSTEM_H

#include <cmath>
#include "../ECS/ECS.h"
#include "../World.h"

class RenderSystem : public System
{
public:
    RenderSystem() = default;
    RenderSystem(World* world, int screen_width, int screen_height)
    {
        RenderSystem::screen_width = screen_width;
        RenderSystem::screen_height = screen_height;
        // Calculate tile_width
        int min_screen = std::max(screen_width,screen_height);
        int max_world = std::max(world->getHeight(),world->getWidth());
        RenderSystem::tile_width = (int)floor(min_screen/max_world);
        //std::cout << "Tile width: " << tile_width << std::endl;
    };
    int getTile_width() const { return tile_width; };
protected:
    int tile_width = 0; // square : width = height
    int screen_width = 0;
    int screen_height = 0;
};

#endif //PACMAN_RENDERSYSTEM_H

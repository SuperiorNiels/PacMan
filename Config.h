//
// Created by niels on 16/03/18.
//

#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H

#include <iostream>
#include <istream>
#include "ECS/ECS.h"
#include "PacMan_Components.h"
#include "TinyXML/tinyxml2.h"
#include "SDL_Factory.h"

using namespace tinyxml2;

class Config
{
public:
    Config() = delete;
    Config(std::string path);
    int getFps() const;
    int getScreen_x() const;
    int getScreen_y() const;
    const std::string &getCollision_map() const;
    const std::string &getSprites_sheet() const;
    AbstractFactory *getFactory() const;
    Entity* createEntity(std::string entity_name, int tile_width, int x=0, int y=0, int x_offset=0, int y_offset = 0);
private:
    AbstractFactory* factory = nullptr;
    XMLDocument doc;
    int fps = 0;
    int screen_x = 0;
    int screen_y = 0;
    int sprite_tile_width = 0;
    std::string collision_map = std::string();
    std::string sprites_sheet = std::string();
};

#endif //PACMAN_CONFIG_H

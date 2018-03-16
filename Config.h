//
// Created by niels on 16/03/18.
//

#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H

#include <iostream>
#include <istream>
#include <map>

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

private:
    int fps = 0;
    int screen_x = 0;
    int screen_y = 0;
    std::string collision_map = std::string();
    std::string sprites_sheet = std::string();
};

#endif //PACMAN_CONFIG_H

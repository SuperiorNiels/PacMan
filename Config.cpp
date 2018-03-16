//
// Created by niels on 16/03/18.
//

#include "Config.h"
#include "TinyXML/tinyxml2.h"

using namespace tinyxml2;

Config::Config(std::string path)
{
    XMLDocument doc;
    doc.LoadFile(path.c_str());
    doc.FirstChildElement("pacman")->FirstChildElement("game")->QueryIntAttribute("fps", &fps);
    doc.FirstChildElement("pacman")->FirstChildElement("game")->QueryIntAttribute("screen_x", &screen_x);
    doc.FirstChildElement("pacman")->FirstChildElement("game")->QueryIntAttribute("screen_y", &screen_y);
    collision_map = doc.FirstChildElement("pacman")->FirstChildElement("game")->FirstChildElement("collision")->GetText();
    sprites_sheet = doc.FirstChildElement("pacman")->FirstChildElement("game")->FirstChildElement("sprites")->GetText();
    std::cout << "config loaded." << std::endl;
}

int Config::getFps() const
{
    return fps;
}

int Config::getScreen_x() const
{
    return screen_x;
}

int Config::getScreen_y() const
{
    return screen_y;
}

const std::string &Config::getCollision_map() const
{
    return collision_map;
}

const std::string &Config::getSprites_sheet() const
{
    return sprites_sheet;
}

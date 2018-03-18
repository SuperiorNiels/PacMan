//
// Created by niels on 16/03/18.
//

#include "Config.h"

Config::Config(std::string path)
{
    //Config::factory = factory;
    doc.LoadFile(path.c_str());
    doc.FirstChildElement("pacman")->FirstChildElement("game")->QueryIntAttribute("fps", &fps);
    doc.FirstChildElement("pacman")->FirstChildElement("game")->QueryIntAttribute("screen_x", &screen_x);
    doc.FirstChildElement("pacman")->FirstChildElement("game")->QueryIntAttribute("screen_y", &screen_y);
    collision_map = doc.FirstChildElement("pacman")->FirstChildElement("game")->FirstChildElement("collision")->GetText();
    sprites_sheet = doc.FirstChildElement("pacman")->FirstChildElement("game")->FirstChildElement("sprites")->GetText();
    doc.FirstChildElement("pacman")->FirstChildElement("game")->FirstChildElement("sprites")->QueryIntAttribute("tile_width", &sprite_tile_width);
    std::string graphics = doc.FirstChildElement("pacman")->FirstChildElement("game")->FirstChildElement("graphics")->GetText();
    if(graphics == "SDL")
    {
        // Create SDL factory
        factory = new SDL_Factory(this);
    }
    std::cout << "Config loaded." << std::endl;
}

Entity* Config::createEntity(std::string entity_name, int tile_width, int x, int y)
{
    auto* entity_config = doc.FirstChildElement("pacman")->FirstChildElement("entities")->FirstChildElement(entity_name.c_str());
    if(entity_config != nullptr)
    {
        std::cout << "entity found." << std::endl;
        Entity* e = new Entity();
        if(entity_config->FirstChildElement("position_component") != nullptr)
        {
            auto* pc = new PositionComponent();
            pc->x = x; pc->y = y;
            e->addComponent(pc);
        }
        if(entity_config->FirstChildElement("collision_component") != nullptr)
        {
            auto* cc = new CollisionComponent();
            cc->collision_box[0] = 0;
            cc->collision_box[1] = 0;
            cc->collision_box[2] = tile_width;
            cc->collision_box[3] = tile_width;
            e->addComponent(cc);
        }
        if(entity_config->FirstChildElement("render_component") != nullptr)
        {
            if(entity_config->FirstChildElement("render_component")->FirstChildElement("clips") != nullptr)
            {
                auto* clip_config = entity_config->FirstChildElement("render_component")->FirstChildElement("clips");
                int total;
                clip_config->QueryIntAttribute("total", &total);
                for(int i=0;i<total;i++)
                {
                    // TODO: maybe add check if clip exists?
                    clip c;
                    clip_config->FirstChildElement("clip");

                }
            }

            //auto* rc = factory->createRenderComponent(sprites_sheet);
            //e->addComponent(rc);
        }
    }
    else
    {
        std::cout << "entity not found." << std::endl;
    }
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

AbstractFactory *Config::getFactory() const
{
    return factory;
}

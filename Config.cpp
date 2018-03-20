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

Entity* Config::createEntity(std::string entity_name, int tile_width, int x, int y, int x_offset, int y_offset)
{
    auto* entity_config = doc.FirstChildElement("pacman")->FirstChildElement("entities")->FirstChildElement(entity_name.c_str());
    if(entity_config != nullptr)
    {
        //std::cout << "entity found." << std::endl;
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
            std::vector<clip> clips = std::vector<clip>();
            auto* render_config = entity_config->FirstChildElement("render_component");
            if(render_config->FirstChildElement("clips") != nullptr)
            {
                auto* clip_config = render_config->FirstChildElement("clips");
                int total;
                clip_config->QueryIntAttribute("total", &total);
                for(int i=0;i<total;i++)
                {
                    clip c;
                    if(i == 0)
                        clip_config = clip_config->FirstChildElement("clip");
                    else
                        clip_config = clip_config->NextSiblingElement();
                    if(clip_config != nullptr)
                    {
                        clip_config->QueryIntAttribute("x",&c.x);
                        clip_config->QueryIntAttribute("y",&c.y);
                        clip_config->QueryIntAttribute("w",&c.w);
                        clip_config->QueryIntAttribute("h",&c.h);
                        int x_off, y_off = 0;
                        render_config->FirstChildElement("clips")->QueryIntAttribute("x_offset", &x_off);
                        render_config->FirstChildElement("clips")->QueryIntAttribute("y_offset", &y_off);
                        c.x = c.x + (x_offset*x_off);
                        c.y = c.y + (y_offset*y_off);
                        if(c.x == -1) c.x = x * sprite_tile_width;
                        if(c.y == -1) c.y = y * sprite_tile_width;
                        if(c.h == -1) c.h = sprite_tile_width;
                        if(c.w == -1) c.w = sprite_tile_width;
                        clips.push_back(c);
                    }
                }
            }
            auto* rc = factory->createRenderComponent(sprites_sheet,clips);
            if(render_config->FirstChildElement("animation_length") != nullptr)
                render_config->FirstChildElement("animation_length")->QueryIntAttribute("value",&rc->animation_length);
            if(render_config->FirstChildElement("animation_speed") != nullptr)
                render_config->FirstChildElement("animation_speed")->QueryIntAttribute("value",&rc->animation_speed);
            if(render_config->FirstChildElement("direction_offset") != nullptr)
            {
                render_config->FirstChildElement("direction_offset")->QueryIntAttribute("left",&rc->direction_offsets[0]);
                render_config->FirstChildElement("direction_offset")->QueryIntAttribute("right",&rc->direction_offsets[1]);
                render_config->FirstChildElement("direction_offset")->QueryIntAttribute("up",&rc->direction_offsets[2]);
                render_config->FirstChildElement("direction_offset")->QueryIntAttribute("down",&rc->direction_offsets[3]);
            }
            rc->scale = tile_width/sprite_tile_width;
            e->addComponent(rc);
        }
        if(entity_config->FirstChildElement("points_component") != nullptr)
        {
            e->addComponent(new PointsComponent());
        }
        if(entity_config->FirstChildElement("movable_component") != nullptr)
        {
            e->addComponent(new MovableComponent());
        }
        if(entity_config->FirstChildElement("player_input_component") != nullptr)
        {
            e->addComponent(new PlayerInputComponent());
        }
        if(entity_config->FirstChildElement("ai_component") != nullptr)
        {
            e->addComponent(new AIComponent());
        }
        return e;
    }
    return nullptr;
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

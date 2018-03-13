//
// Created by niels on 13/03/18.
//


#include "World.h"

World::World(std::string world_file)
{
    std::ifstream in(world_file);

    width = 0; in >> width;
    height = 0; in >> height;
    world = new int*[height];
    for(int x=0;x<height;x++)
    {
        world[x] = new int[width];
        for(int y=0;y<width;y++) {
            in >> world[x][y];
        }
    }
}

int **World::getWorld() const {
    return world;
}

int World::getWidth() const {
    return width;
}

int World::getHeight() const {
    return height;
}

World::~World()
{
    delete world;
}

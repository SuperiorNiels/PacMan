//
// Created by niels on 13/03/18.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H

#include <iostream>
#include <fstream>

class World
{
public:
    explicit World(std::string world_file);
    int **getWorld() const;
    int getWidth() const;
    int getHeight() const;
    ~World();
private:
    int **world = nullptr;
    int width = 0;
    int height = 0;
};


#endif //PACMAN_WORLD_H

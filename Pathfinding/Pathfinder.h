//
// Created by niels on 06/04/18.
//

#ifndef PACMAN_PATHFINDER_H
#define PACMAN_PATHFINDER_H

#include <vector>
#include "../World.h"
#include "PathNode.h"

class Pathfinder
{
public:
    Pathfinder() = default;
    explicit Pathfinder(World* world) { Pathfinder::world = world; };
    virtual std::vector<PathNode> getPath(int start_x, int start_y, int stop_x, int stop_y) = 0;
protected:
    World* world = nullptr;
};

#endif //PACMAN_PATHFINDER_H

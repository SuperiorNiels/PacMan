//
// Created by niels on 06/04/18.
//

#ifndef PACMAN_A_STAR_H
#define PACMAN_A_STAR_H

#include <cmath>
#include <vector>
#include <map>
#include "../World.h"
#include "Node.h"
#include "Pathfinder.h"

class A_star : public Pathfinder
{
public:
    A_star() = delete;
    A_star(World* world) : Pathfinder(world) {};
    std::vector<Node*> getPath(int start_x, int start_y, int stop_x, int stop_y) override;
private:
    double calculateDistance(int x1, int x2, int y1, int y2);
};


#endif //PACMAN_A_STAR_H

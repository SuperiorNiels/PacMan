//
// Created by niels on 06/04/18.
//

#ifndef PACMAN_A_STAR_H
#define PACMAN_A_STAR_H

#include <cmath>
#include <vector>
#include <queue>
#include "Pathfinder.h"
#include "PathNode.h"
#include "../World.h"
#include "../PacMan_Constants.h"

class A_star : public Pathfinder
{
public:
    A_star() = delete;
    explicit A_star(World* world) : Pathfinder(world) {};
    std::vector<PathNode> getPath(int start_x, int start_y, int stop_x, int stop_y) override;
private:
    double calculateDistance(int x1, int x2, int y1, int y2);
    std::vector<PathNode> getNeighbors(PathNode* a);
    bool pathNodeInVector(std::vector<PathNode>* vector, PathNode* a);
    bool pathNodeInPriorityQueue(std::priority_queue<PathNode> vector, PathNode *a);
};

#endif //PACMAN_A_STAR_H

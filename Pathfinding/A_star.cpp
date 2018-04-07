//
// Created by niels on 06/04/18.
//

#include "A_star.h"

std::vector<PathNode*> A_star::getPath(int start_x, int start_y, int stop_x, int stop_y)
{
    std::priority_queue<PathNode> open = std::priority_queue<PathNode>();
    PathNode start_node = PathNode(start_x, start_y);
    open.emplace(start_node);

    while(!open.empty())
    {
        PathNode current_node = open.top();
        open.pop();

        if(current_node.getX() == stop_x && current_node.getY() == stop_y)
            break;

    }

    return std::vector<PathNode*>();
}

double A_star::calculateDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x1-x2,2.f) + pow(y1-y2,2.f));
}
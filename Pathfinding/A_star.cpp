//
// Created by niels on 06/04/18.
//

#include "A_star.h"
#include "../PacMan_Constants.h"

std::vector<PathNode> A_star::getPath(int start_x, int start_y, int stop_x, int stop_y)
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

    std::vector<PathNode> test = getNeighbors(&start_node);

    return std::vector<PathNode>();
}

std::vector<PathNode> A_star::getNeighbors(PathNode* a)
{
    std::vector<PathNode> neighbors = std::vector<PathNode>();
    for(int i=1;i<5;i++)
    {
        int neighbor_x = a->getX() + movement_vector[i][0];
        int neighbor_y = a->getY() + movement_vector[i][1];

        if(neighbor_x < 0)
            neighbor_x = 0;
        if(neighbor_x > A_star::world->getWidth()-1)
            neighbor_x = A_star::world->getWidth()-1;
        if(neighbor_y < 0)
            neighbor_y = 0;
        if(neighbor_y > A_star::world->getHeight()-1)
            neighbor_y = A_star::world->getHeight()-1;

        int tile = A_star::world->getWorld()[neighbor_x][neighbor_y];
        if(tile != 1)
        {
            PathNode neighbor = PathNode(neighbor_x,neighbor_y);
            neighbor.setParent(a);
            if(!checkIfPathNodeInVector(&neighbors, &neighbor))
                neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

bool A_star::checkIfPathNodeInVector(std::vector<PathNode> *vector, PathNode *a)
{
    for(auto node : *vector)
    {
        if(*a == node)
            return true;
    }
    return false;
}

double A_star::calculateDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x1-x2,2.f) + pow(y1-y2,2.f));
}
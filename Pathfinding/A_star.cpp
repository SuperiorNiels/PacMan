//
// Created by niels on 06/04/18.
//

#include <unordered_set>
#include <cstring>
#include "A_star.h"

std::vector<PathNode> A_star::getPath(int start_x, int start_y, int stop_x, int stop_y)
{
    std::priority_queue<PathNode> open = std::priority_queue<PathNode>();
    PathNode start_node = PathNode(start_x, start_y);
    start_node.setG(0);
    start_node.setPriority(calculateDistance(start_x,start_y,stop_x,stop_y));
    open.emplace(start_node);

    std::vector<PathNode> closed = std::vector<PathNode>();

    PathNode current_node;
    while(!open.empty())
    {
        current_node = open.top();
        open.pop();
        closed.push_back(current_node);

        if(current_node.getX() == stop_x && current_node.getY() == stop_y)
            break;

        std::vector<PathNode> neighbors = getNeighbors(&current_node);

        for(auto& neighbor : neighbors)
        {
            if(pathNodeInVector(&closed,&neighbor))
                continue; // already checked

            double score = current_node.getG() + calculateDistance(current_node.getX(), current_node.getY(),
                                                                   neighbor.getX(), neighbor.getY());
            if(score >= neighbor.getG())
                continue; // not a better path

            neighbor.setG(score);
            neighbor.setH(calculateDistance(neighbor.getX(),neighbor.getY(),stop_x,stop_y));
            neighbor.setPriority(neighbor.getG() + neighbor.getH());

            if(!pathNodeInPriorityQueue(open, &neighbor))
                open.emplace(neighbor);
        }
    }

    std::vector<PathNode> path = std::vector<PathNode>();

    while(!(current_node == start_node)) // fixme: for loop weg (idee: came_from map bijhouden => parents hier bijhouden)
    {
        path.push_back(current_node);
        for(auto& node : closed)
        {
            if(node == PathNode(current_node.getParent_x(),current_node.getPatent_y()))
                current_node = node;
        }
    }

    return path;
}

std::vector<PathNode> A_star::getNeighbors(PathNode* a)
{
    std::vector<PathNode> neighbors = std::vector<PathNode>(); // fixme: vector or unordered_set?
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

        int tile = A_star::world->getWorld()[neighbor_y][neighbor_x];
        if(tile != 1)
        {
            PathNode neighbor = PathNode(neighbor_x,neighbor_y);
            neighbor.setParent_x(a->getX());
            neighbor.setPatent_y(a->getY());
            if(!pathNodeInVector(&neighbors, &neighbor))
                neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

bool A_star::pathNodeInVector(std::vector<PathNode> *vector, PathNode *a)
{
    for(auto node : *vector)
    {
        if(*a == node)
            return true;
    }
    return false;
}

bool A_star::pathNodeInPriorityQueue(std::priority_queue<PathNode> vector, PathNode *a)
{
    while(!vector.empty())
    {
        PathNode b = vector.top();
        if(*a == b)
            return true;
        vector.pop();
    }
    return false;
}

double A_star::calculateDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x1-x2,2.f) + pow(y1-y2,2.f));
}
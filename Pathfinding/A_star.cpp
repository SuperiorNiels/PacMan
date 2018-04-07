//
// Created by niels on 06/04/18.
//

#include "A_star.h"

std::vector<Node*> A_star::getPath(int start_x, int start_y, int stop_x, int stop_y)
{
    std::map<double, Node> open = std::map<double, Node>();
    open.insert(std::pair<double, Node>(0,Node(start_x,start_y)));
    open.insert(std::pair<double, Node>(9.31561,Node(start_x,start_y)));

    open.clear();
    std::cout << "path found " << std::endl;
}

double A_star::calculateDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x1-x2,2.f) + pow(y1-y2,2.f));
}
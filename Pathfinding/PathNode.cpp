//
// Created by niels on 05/04/18.
//

#include "PathNode.h"

PathNode::PathNode(int x, int y)
{
    PathNode::x = x;
    PathNode::y = y;
}

PathNode *PathNode::getParent() const
{
    return parent;
}

void PathNode::setParent(PathNode *parent)
{
    PathNode::parent = parent;
}

double PathNode::getPriority() const
{
    return priority;
}

void PathNode::setPriority(double priority)
{
    PathNode::priority = priority;
}

bool operator<(const PathNode &a, const PathNode &b)
{
    return a.getPriority() > b.getPriority();
}

int PathNode::getX() const {
    return x;
}

void PathNode::setX(int x) {
    PathNode::x = x;
}

int PathNode::getY() const {
    return y;
}

void PathNode::setY(int y) {
    PathNode::y = y;
}

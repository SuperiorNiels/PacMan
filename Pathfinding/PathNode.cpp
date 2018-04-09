//
// Created by niels on 05/04/18.
//

#include "PathNode.h"

PathNode::PathNode(int x, int y)
{
    PathNode::x = x;
    PathNode::y = y;
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

bool operator==(const PathNode &a, const PathNode &b)
{
    return a.getX() == b.getX() && a.getY() == b.getY();
}

int PathNode::getX() const
{
    return x;
}

void PathNode::setX(int x)
{
    PathNode::x = x;
}

int PathNode::getY() const
{
    return y;
}

void PathNode::setY(int y)
{
    PathNode::y = y;
}

double PathNode::getG() const
{
    return g;
}

void PathNode::setG(double g)
{
    PathNode::g = g;
}

double PathNode::getH() const
{
    return h;
}

void PathNode::setH(double h)
{
    PathNode::h = h;
}
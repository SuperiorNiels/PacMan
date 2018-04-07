//
// Created by niels on 05/04/18.
//

#include "Node.h"

Node::Node(int x, int y)
{
    Node::x = x;
    Node::y = y;
}

Node *Node::getParent() const
{
    return parent;
}

void Node::setParent(Node *parent)
{
    Node::parent = parent;
}

Node::~Node()
{
    delete parent;
}
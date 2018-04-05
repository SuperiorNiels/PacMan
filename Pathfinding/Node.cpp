//
// Created by niels on 05/04/18.
//

#include "Node.h"

Node::Node(int x, int y)
{
    Node::x = x;
    Node::y = y;
}

Node *Node::getPrevious() const {
    return previous;
}

void Node::setPrevious(Node *previous) {
    Node::previous = previous;
}

Node *Node::getNext() const {
    return next;
}

void Node::setNext(Node *next) {
    Node::next = next;
}

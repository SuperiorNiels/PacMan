//
// Created by niels on 05/04/18.
//

#ifndef PACMAN_NODE_H
#define PACMAN_NODE_H


class Node
{
public:
    Node() = delete;
    Node(int x, int y);
    Node *getParent() const;
    void setParent(Node *parent);
    ~Node();
private:
    int x = 0;
    int y = 0;
    Node* parent = nullptr;
};


#endif //PACMAN_NODE_H

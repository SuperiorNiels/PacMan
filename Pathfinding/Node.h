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
    Node *getPrevious() const;
    void setPrevious(Node *previous);
    Node *getNext() const;
    void setNext(Node *next);
private:
    int x = 0;
    int y = 0;
    Node* previous = nullptr;
    Node* next = nullptr;

};


#endif //PACMAN_NODE_H

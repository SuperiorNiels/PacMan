//
// Created by niels on 05/04/18.
//

#ifndef PACMAN_NODE_H
#define PACMAN_NODE_H


class PathNode
{
public:
    PathNode() = default;
    PathNode(int x, int y);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    PathNode *getParent() const;
    void setParent(PathNode *parent);
    void setPriority(double priority);
    double getPriority() const;
    friend bool operator<(const PathNode& a, const PathNode& b);
    ~PathNode() = default;
private:
    int x = 0;
    int y = 0;
    double priority = 0;
    PathNode* parent = nullptr;
};


#endif //PACMAN_NODE_H
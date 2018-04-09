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
    int getParent_x() const;
    void setParent_x(int parent_x);
    int getPatent_y() const;
    void setPatent_y(int patent_y);
    void setPriority(double priority);
    double getPriority() const;
    double getG() const;
    void setG(double g);
    double getH() const;
    void setH(double h);
    friend bool operator<(const PathNode& a, const PathNode& b);
    friend bool operator==(const PathNode& a, const PathNode& b);
    ~PathNode() = default;
protected:
    int x = 0;
    int y = 0;
    double priority = 0;
    double g = 9999;
    double h = 0;
    //PathNode* parent = nullptr;
    int parent_x = 0;
    int patent_y = 0;
};


#endif //PACMAN_NODE_H
#ifndef NODE_H
#define NODE_H

#include <QVector>

class Node
{
public:
    Node();
    Node(int x, int y);

    int x, y;
    int traversability = 100;
    int regionIndex = -1;
    int gCost = 0;
    int hCost = 0;
    int fCost();
    int heapIndex = 0;
    Node* parent = nullptr;

    bool IsTraversable();
    int CompareTo(Node* nodeB);
};

#endif // NODE_H

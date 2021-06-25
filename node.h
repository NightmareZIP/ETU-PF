#ifndef NODE_H
#define NODE_H


class Node
{
public:
    Node();
    Node(int x, int y);

    int x, y;
    int traversability;

    bool IsTraversable()
    {
        return traversability > 0;
    }
};

#endif // NODE_H

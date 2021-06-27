#include "node.h"

Node::Node(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Node::fCost()
{
    return gCost + hCost;
}

bool Node::IsTraversable()
{
    return traversability != 0;
}

int Node::CompareTo(Node *nodeB)
{
    int compare = 0;
    if (fCost() > nodeB->fCost())
    {
        compare = 1;
    }
    else if (fCost() == nodeB->fCost())
    {

        if (hCost > nodeB->hCost)
        {
            compare = 1;
        }
        else if (hCost == nodeB->hCost)
        {
            compare = 0;
        }
        else
        {
            compare = -1;
        }
    }
    else
    {
        compare = -1;
    }

    //если шото не работает попробуй минус 1
    return -compare;
}

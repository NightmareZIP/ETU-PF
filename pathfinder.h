#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "node.h"
#include "map.h"

class Pathfinder
{
public:
    Pathfinder();

    static QVector<Node*> FindPath(Node *startNode, Node *targetNode, Map* map);
};

#endif // PATHFINDER_H

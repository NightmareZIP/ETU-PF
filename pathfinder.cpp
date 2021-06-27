#include "pathfinder.h"
#include <qelapsedtimer.h>
#include <QtDebug>
#include "minheap.h"
#include "map.h"

Pathfinder::Pathfinder()
{

}

int Heuristic(Node* A, Node* B) {
    // Octile
    int dx = abs(A->x - B->x);
    int dy = abs(A->y - B->y);
    return 10 * (dx + dy) + (14 - 2 * 10) * min(dx, dy);
}

int GetDistance(Node* A, Node* B) {
    double aTraversability = (double) 100 / (double) A->traversability;
    double bTraversability = (double) 100 / (double) B->traversability;
    int distX = abs(A->x - B->x)*aTraversability;
    int distY = abs(A->y - B->y)*bTraversability;
    if(distX > distY) {
        return 14 * distY + 10 * (distX - distY);
    }
    return 14 * distX + 10 * (distY - distX);
}

QVector<Node*> RetracePath(Node* startNode, Node* currentNode) {
    QVector<Node*> path;
    do {
        path.insert(0, currentNode);
        currentNode = currentNode->parent;
    } while (currentNode != startNode);
    return path;
}

QVector<Node *> Pathfinder::FindPath(Node *startNode, Node *targetNode, Map* map)
{
    QVector<Node*> path;

    if (startNode == targetNode)
    {
        return path;
    }

    if (startNode->regionIndex != targetNode->regionIndex)
    {
        qDebug() << "Way does not exist.";
        return path;
    }

    MinHeap openSet;
    openSet.Initialize(map->GetSize() * map->GetSize());
    QSet<Node*> closedSet;
    openSet.Add(startNode);

    while (openSet.Count > 0)
    {
        Node* currentNode = openSet.RemoveFirst();
        closedSet.insert(currentNode);

        if (currentNode == targetNode)
        {
            path = RetracePath(startNode, targetNode);
            return path;
        }

        QVector<Node*> neighbours = map->GetNeighbours(currentNode);
        for (int i = 0; i < neighbours.count(); i++)
        {
            Node* neighbour = neighbours.value(i);
            if (closedSet.contains(neighbour) || !neighbour->IsTraversable()) {
                continue;
            }

            int newCostToNeighbour = currentNode->gCost + GetDistance(currentNode, neighbour);
            if (openSet.Contains(neighbour)) {
                if (newCostToNeighbour < neighbour->gCost) {
                    neighbour->gCost = newCostToNeighbour;
                    neighbour->hCost = Heuristic(neighbour, targetNode);
                    neighbour->parent = currentNode;
                    openSet.UpdateItem(neighbour);
                }
            } else {
                neighbour->gCost = newCostToNeighbour;
                neighbour->hCost = Heuristic(neighbour, targetNode);
                neighbour->parent = currentNode;

                openSet.Add(neighbour);
            }
        }
    }

    return path;
}

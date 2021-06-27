#include "floodfill.h"

#include <qelapsedtimer.h>
#include <QDebug>
#include <QQueue>

FloodFill::FloodFill()
{

}

void ResetNodes(DataManager *dataManager)
{
    for (int x = 0; x < dataManager->map->GetSize(); x++)
    {
        for (int y = 0; y < dataManager->map->GetSize(); y++)
        {
            Node* node = dataManager->map->NodeAt(x, y);
            node->regionIndex = -1;
            node->gCost=0;
            node->hCost=0;
            node->parent=nullptr;
            node->heapIndex=0;
        }
    }
}

void FillFrom(Node *startNode, int regionIndex, DataManager* dataManager)
{
    QQueue<Node*> nodeQueue;
    nodeQueue.enqueue(startNode);
    startNode->regionIndex = regionIndex;

    while (nodeQueue.count() != 0)
    {
        QVector<Node*> neighbours = dataManager->map->GetNeighbours(nodeQueue.dequeue());
        for (int i = 0; i < neighbours.count(); i++)
        {
            Node* neighbourNode = neighbours.value(i);
            if (neighbourNode->IsTraversable() && neighbourNode->regionIndex != regionIndex)
            {
                nodeQueue.enqueue(neighbourNode);
                neighbourNode->regionIndex = regionIndex;
            }
        }
    }
}

void FloodFill::FillRegions(DataManager *dataManager)
{
    QElapsedTimer timer;
    timer.start();

    ResetNodes(dataManager);

    int currentRegionIndex = -1;

    for (int x = 0; x < dataManager->map->GetSize(); x++)
    {
        for (int y = 0; y < dataManager->map->GetSize(); y++)
        {
            Node* node = dataManager->map->NodeAt(x, y);
            if (node->IsTraversable() && node->regionIndex == -1)
            {
                currentRegionIndex++;
                FillFrom(node, currentRegionIndex, dataManager);
            }
        }
    }

    qDebug() << "Created " << (currentRegionIndex+1) << " regions in " << timer.elapsed() << "ms.";
}

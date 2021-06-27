#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVector>
#include <QPoint>
#include <polygonstruct.h>
#include <map.h>
#include <QPolygon>
class DataManager
{
public:
    explicit DataManager();

    PolygonStruct* TryCreateNewPolygon(QVector<QPoint> pointList, bool& result);

    void BuildMap();
    void ConvertPathToBLine();
    QVector<Node*> BresenhamLine();
    bool CanPullNodes(Node* nodeA, Node* nodeB);
    void PullPath(int pass);

    QVector<QPoint> newPolygonPoints;
    int newPolygonTraversability = 0;

    QVector<Node*> lastFoundPathOriginal;
    QVector<Node*> lastFoundPath;
    QVector<Node*> bLine;

    QVector<PolygonStruct*> polygonList;
    Map* map;
    Node* startNode = nullptr;
    Node* endNode = nullptr;
};

#endif // DATAMANAGER_H

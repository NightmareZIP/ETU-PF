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

    QVector<QPoint> newPolygonPoints;
    int newPolygonTraversability = 0;

    QVector<Node*> lastFoundPath;

    QVector<PolygonStruct*> polygonList;
    Map* map;
    Node* startNode = nullptr;
    Node* endNode = nullptr;
};

#endif // DATAMANAGER_H

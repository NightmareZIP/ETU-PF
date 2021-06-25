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
    void TryDeletePolygon(int ind);

    QVector<QPoint> newPolygonPoints;
    int newPolygonTraversability = 0;

    QVector<PolygonStruct*> polygonList;
    Map* map;
    Node* startNode = nullptr;
    Node* endNode = nullptr;
};

#endif // DATAMANAGER_H

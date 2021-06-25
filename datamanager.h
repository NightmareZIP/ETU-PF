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
    QVector<PolygonStruct*> GetAllPolygons();
    Map* GetMap();

private:
    QVector<PolygonStruct*> PolygonList;
    Map* map;
};

#endif // DATAMANAGER_H

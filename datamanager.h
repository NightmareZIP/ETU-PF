#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVector>
#include <QPoint>
#include <polygonstruct.h>
#include <map.h>

class DataManager
{
public:
    explicit DataManager();

    PolygonStruct* TryCreateNewPolygon(QVector<QPoint> pointList, bool& result);
    QVector<PolygonStruct*> GetAllPolygons();
    Map* GetMap();

private:
    QVector<PolygonStruct*> PolygonList;
    Map* map;
};

#endif // DATAMANAGER_H

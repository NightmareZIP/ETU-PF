#include "datamanager.h"
#include <QDebug>

DataManager::DataManager()
{
    map = new Map();
}

PolygonStruct* DataManager::TryCreateNewPolygon(QVector<QPoint> pointList, bool &result)
{
    if (pointList.count() >= 3)
    {
        QPolygon* newPolygon = new QPolygon(pointList);
        PolygonStruct* ps = new PolygonStruct(newPolygon);
        PolygonList.append(ps);
        qDebug() << "Created new polygon.";
        result = true;
        return ps;
    }
    result = false;
    return nullptr;
}
void DataManager::TryDeletePolygon(int ind){
    PolygonStruct *polygon = PolygonList.value(ind);
     PolygonList.remove(ind,1);
    delete polygon;

}
QVector<PolygonStruct*> DataManager::GetAllPolygons()
{
    return PolygonList;
}

Map *DataManager::GetMap()
{
    return map;
}

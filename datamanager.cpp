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
        ps->SetTraversability(newPolygonTraversability);
        polygonList.append(ps);
        result = true;
        return ps;
    }
    result = false;
    return nullptr;
}

void DataManager::TryDeletePolygon(int ind){
    PolygonStruct *polygon = polygonList.value(ind);
     polygonList.remove(ind,1);
    delete polygon;

}

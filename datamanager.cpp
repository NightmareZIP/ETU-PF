#include "datamanager.h"
#include <QDebug>
#include <qelapsedtimer.h>

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

void DataManager::BuildMap()
{
    QElapsedTimer timer;
    timer.start();

    //максимально не оптимизированно, но у меня нет других идей
    for (int x = 0; x < map->GetSize(); x++)
    {
        for (int y = 0; y < map->GetSize(); y++)
        {
            QPoint* point = new QPoint(x, y);
            for (int i = polygonList.count() - 1; i >= 0; i--)
            {
                PolygonStruct* ps = polygonList.value(i);
                if (ps->GetPolygon()->containsPoint(*point, Qt::WindingFill))
                {
                    map->NodeAt(x, y)->traversability = ps->GetTraversability();
                    break;
                }
            }
            delete point;
        }
    }

    qDebug() << "Building of map took" << timer.elapsed() << "milliseconds";
}

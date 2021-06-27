#include "datamanager.h"
#include <QDebug>
#include <qelapsedtimer.h>
#include "floodfill.h"

DataManager::DataManager()
{
    map = new Map();
}

//Функция пытается создать новый полигон на выбранных клетках
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

//Функция производит подготовку карты для дальнейшей работы с ней через A*
void DataManager::BuildMap()
{
    QElapsedTimer timer;
    timer.start();

    //устанавливаем проходимость для каждой клетки
    for (int x = 0; x < map->GetSize(); x++)
    {
        for (int y = 0; y < map->GetSize(); y++)
        {
            QPoint* point = new QPoint(x, y);
            map->NodeAt(x, y)->traversability = 100;
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

    //заполняем регионы проходимости
    FloodFill::FillRegions(this);

    qDebug() << "Building of map took" << timer.elapsed() << "milliseconds";
}

//функция проверяет можно ли стянуть проход между двумя клетками
//создает прямую и ищет пересечения с другими полигонами
//если пересечений нет или они проходят по полигонам с меньшей проходимостью,
//то мы можем "стянуть" клетки
bool DataManager::CanPullNodes(Node* nodeA, Node* nodeB)
{
    QVector<QPoint> linePoints;
    linePoints.append(*new QPoint(nodeA->x, nodeA->y));
    linePoints.append(*new QPoint(nodeB->x, nodeB->y));
    QPolygon* line = new QPolygon(linePoints);
    int lineTraversability = nodeA->traversability;

    for (int i = polygonList.count() - 1; i >= 0; i--)
    {
        PolygonStruct* ps = polygonList.value(i);
        if (ps->GetPolygon()->intersects(*line))
        {
            if (lineTraversability > ps->GetTraversability() || ps->GetTraversability() == 0)
            {
                return false;
            }
        }
    }

    delete line;
    return true;
}

//функция "стягивает" путь до более оптипального для человеческого взгляда
//используется две проходки для стягивания сперва с одной стороны, а потом с другой
void DataManager::PullPath(int pass)
{
    bLine.clear();
    if (pass % 2 == 0)
    {
        for (int i = 0; i < lastFoundPath.count(); i++)
        {
            Node* nodeA = lastFoundPath.value(i);
            int nTraversability = nodeA->traversability;
            bLine.append(nodeA);

            for (int j = lastFoundPath.count()-1; j > i; j--)
            {
                Node* nodeB = lastFoundPath.value(j);
                if (nodeB->traversability >= nTraversability)
                {
                    if (CanPullNodes(nodeA, nodeB))
                    {
                        bLine.append(nodeB);
                        i = j;
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
    else
    {
        for (int i = lastFoundPath.count() - 1; i >= 0; i--)
        {
            Node* nodeA = lastFoundPath.value(i);
            int nTraversability = nodeA->traversability;
            bLine.append(nodeA);

            for (int j = 0; j < i; j++)
            {
                Node* nodeB = lastFoundPath.value(j);
                if (nodeB->traversability >= nTraversability)
                {
                    if (CanPullNodes(nodeA, nodeB))
                    {
                        bLine.append(nodeB);
                        i = j;
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

//последовательность действий для конвертирования пути,
//сгенерированного A* в стянутый путь
void DataManager::ConvertPathToBLine()
{
    PullPath(0);
    lastFoundPath = BresenhamLine();
    PullPath(1);
    lastFoundPath = BresenhamLine();
}

//стандартная дискретизация пути из линий в клетки на карте
//методом Брезенхэма
QVector<Node*> DataManager::BresenhamLine()
{
    QVector<Node*> discretePath;

    for (int i = 0; i < bLine.count()-1; i++)
    {
        Node* nodeA = bLine.value(i);
        Node* nodeB = bLine.value(i+1);

        int x1 = nodeA->x;
        int x2 = nodeB->x;
        int y1 = nodeA->y;
        int y2 = nodeB->y;

        const int deltaX = abs(x2 - x1);
        const int deltaY = abs(y2 - y1);
        const int signX = x1 < x2 ? 1 : -1;
        const int signY = y1 < y2 ? 1 : -1;
        int error = deltaX - deltaY;

        while(x1 != x2 || y1 != y2)
        {
            discretePath.append(map->NodeAt(x1, y1));
            int error2 = error * 2;
            if(error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }
            if(error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
        }
    }

    discretePath.append(bLine.last());

    return discretePath;
}

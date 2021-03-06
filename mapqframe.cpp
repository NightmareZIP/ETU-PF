#include "mapqframe.h"
#include <QElapsedTimer>
#include <QPainter>
#include <QPoint>
#include <Qt>
#include <datamanager.h>

MapQFrame::MapQFrame(QWidget* parent) : QFrame(parent)
{

}

void MapQFrame::Repaint(DataManager *dataManager)
{
    this->dataManager = dataManager;
    repaint();
}

void MapQFrame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (dataManager != nullptr)
    {

        //отрисовка полигонов
        DrawPolygons(painter);

        //отрисовка клеток для нового полигона
        for (int i = 0; i < dataManager->newPolygonPoints.length(); i++)
        {
            QPoint point = dataManager->newPolygonPoints.value(i);
            QColor* color = new QColor(0, 0, 0);
            DrawCircle(painter, point.x(), point.y(), *color, 5);
            delete color;
        }

        //отрисовка начальной точки
        if (dataManager->startNode != nullptr)
        {
            QColor* color = new QColor(49, 145, 37);
            DrawCircle(painter, dataManager->startNode->x, dataManager->startNode->y, *color, 5);
            delete color;
        }

        //отрисовка конечной точки
        if (dataManager->endNode != nullptr)
        {
            QColor* color = new QColor(203, 34, 34);
            DrawCircle(painter, dataManager->endNode->x, dataManager->endNode->y, *color, 5);
            delete color;
        }

        if (showOriginalPath)
        {
            //отрисовка оригинального пути, созданного с помощью A* (сиреневый цвет)
            for (int i = 0; i < dataManager->lastFoundPathOriginal.count(); i++)
            {
                Node* node = dataManager->lastFoundPathOriginal.value(i);
                QColor* color = new QColor(33, 234, 224);
                DrawCircle(painter, node->x, node->y, *color, 1);
                delete color;
            }
        }

        if (showPulledPath)
        {
            //отрисовка сжатого пути (желтый цвет)
            for (int i = 0; i < dataManager->lastFoundPath.count(); i++)
            {
                Node* node = dataManager->lastFoundPath.value(i);
                QColor* color = new QColor(223, 234, 33);
                DrawCircle(painter, node->x, node->y, *color, 1);
                delete color;
            }
        }
    }

    painter.end();
}

//функция для рисования круга
void MapQFrame::DrawCircle(QPainter& painter, int x, int y, QColor color, int size)
{
    painter.setPen(color);
    painter.setBrush(*new QBrush(color));
    painter.drawEllipse(x, y, size, size);
}

//функция для отрисовки полигонов
void MapQFrame::DrawPolygons(QPainter& painter)
{
    QColor color = *new QColor(255, 255, 255);
    painter.setPen(color);
    //Draw all polygons
    QVector<PolygonStruct*> polygons = dataManager->polygonList;
    for (int i = 0; i < polygons.count(); i++)
    {
        PolygonStruct* polygon = polygons.value(i);
        if (polygon->GetTraversability() == 0)
        {
            QColor* color = new QColor(14, 45, 157);
            painter.setBrush(*new QBrush(*color, Qt::SolidPattern));
            delete color;
        }
        else
        {
            int rgb = polygon->GetTraversability() * 2.55;
            painter.setBrush(*new QBrush(*new QColor(rgb, rgb, rgb), Qt::SolidPattern));
        }
        painter.drawPolygon(*polygon->GetPolygon(), Qt::WindingFill);
    }
}

void MapQFrame::mousePressEvent(QMouseEvent* ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        int xPos = ev->position().x();
        int yPos = ev->position().y();
        emit OnMousePressed(xPos, yPos);

        repaint();
    }
}

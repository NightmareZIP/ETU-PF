#include "mapqframe.h"
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
        //start node
        if (dataManager->startNode != nullptr)
        {
            QColor* color = new QColor(49, 145, 37);
            DrawCircle(painter, dataManager->startNode->x, dataManager->startNode->y, *color, 5);
            delete color;
        }

        //end node
        if (dataManager->endNode != nullptr)
        {
            QColor* color = new QColor(203, 34, 34);
            DrawCircle(painter, dataManager->endNode->x, dataManager->endNode->y, *color, 5);
            delete color;
        }

        //new polygon points
        for (int i = 0; i < dataManager->newPolygonPoints.length(); i++)
        {
            QPoint point = dataManager->newPolygonPoints.value(i);
            QColor* color = new QColor(0, 0, 0);
            DrawCircle(painter, point.x(), point.y(), *color, 5);
            delete color;
        }

        //draw all polygons
        DrawPolygons();
    }

    painter.end();
}

void MapQFrame::DrawCircle(QPainter& painter, int x, int y, QColor color, int size)
{
    painter.setBrush(*new QBrush(color));
    painter.drawEllipse(x, y, size, size);
}

void MapQFrame::DrawPolygons()
{
    QPainter painter(this);
    //Draw all polygons
    QVector<PolygonStruct*> polygons = dataManager->polygonList;
    for (int i = 0; i < polygons.count(); i++)
    {
        PolygonStruct* polygon = polygons.value(i);
        int rgb = polygon->GetTraversability() * 2.55;
        if (polygon->GetTraversability() == 0)
        {
            painter.setBrush(*new QBrush(*new QColor(rgb, rgb, rgb), Qt::SolidPattern));
        }
        else
        {
            painter.setBrush(*new QBrush(*new QColor(rgb, rgb, rgb), Qt::Dense2Pattern));
        }
        painter.drawPolygon(*polygon->GetPolygon(), Qt::WindingFill);
    }
    painter.end();
}

void MapQFrame::DrawNode(Node *node, QColor* color)
{
    /*
    QPainter painter(this);
    painter.setPen(*color);
    painter.drawPoint(node->x, node->y);
        painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(dataManager->startNode->x, dataManager->startNode->y, 5, 5);


        painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(dataManager->endNode->x, dataManager->endNode->y, 5, 5);
        */
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

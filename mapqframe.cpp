#include "mapqframe.h"

MapQFrame::MapQFrame(QWidget* parent) : QFrame(parent)
{

}

void MapQFrame::mousePressEvent(QMouseEvent* ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        emit OnMousePressed(ev->x(), ev->y());
    }
}

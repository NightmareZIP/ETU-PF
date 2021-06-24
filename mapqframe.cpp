#include "mapqframe.h"
#include <QPainter>

MapQFrame::MapQFrame(QWidget* parent) : QFrame(parent)
{

}

void MapQFrame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
        painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(StartX, StartY, 5, 5);

        painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(FinishX, FinishY, 5, 5);

        //попытка прописать рисование точек текущего создающегося полигона
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap));
        for (int i = 0; i < NewPolygon->size(); i++)
        {
        QPoint* nx = NewPolygon[i][0];

        painter.drawEllipse(NewPolygon[0][1]->x(), NewPolygon[0][i]->y(), 5, 5);
        }
}

void MapQFrame::mousePressEvent(QMouseEvent* ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        if (StartMode)
        {
            StartX=ev->x();
            StartY=ev->y();
        }
        if (FinishMode)
        {
            FinishX=ev->x();
            FinishY=ev->y();
        }
        if (NewPolygonMode)
        {
            //записываем очередную точку полигона
            QPoint* PolygonPoint = new QPoint();
            PolygonPoint->rx()=ev->x();
            PolygonPoint->ry()=ev->y();
            NewPolygon->append(PolygonPoint);
        }
        repaint();
        emit OnMousePressed(ev->x(), ev->y());

    }
}

void MapQFrame::changeStartMode()
{
    StartMode=!StartMode;
    FinishMode=false;
    NewPolygonMode=false;
    emit ChangeButtons(StartMode, FinishMode, NewPolygonMode);
}

void MapQFrame::changeFinishMode()
{
    FinishMode=!FinishMode;
    StartMode=false;
    NewPolygonMode=false;
    emit ChangeButtons(StartMode, FinishMode, NewPolygonMode);
}

void MapQFrame::changeNewPolygonMode()
{
    NewPolygonMode=!NewPolygonMode;
    StartMode=false;
    FinishMode=false;
    emit ChangeButtons(StartMode, FinishMode, NewPolygonMode);

    if (NewPolygonMode) //если только включили режим
    {
        NewPolygon = new QVector<QPoint*>; //создаем вектор/массив для точек полигон
    }
    else if (NewPolygon->length()!=0) //если выключаем режим
    {
        PolygonList.push_back(NewPolygon); //вносим получившийся полигон (если он не пустой) в список полигонов
    }
}


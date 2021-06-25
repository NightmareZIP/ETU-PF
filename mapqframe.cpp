#include "mapqframe.h"
#include <QPainter>
#include <QPoint>
#include <Qt>
#include <datamanager.h>

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
    if (NewPointsVector.length() != 0 and NewPolygonMode){
        for (int i = 0; i < NewPointsVector.length(); i++)
        {
            //QPoint nx = NewPolygon;
            painter.drawEllipse(NewPointsVector.value(i).x(), NewPointsVector.value(i).y(), 5, 5);
        }
    }

    painter.end();

    DrawPolygons();
}

void MapQFrame::DrawPolygons()
{
    QPainter painter(this);
    //Draw all polygons
    QVector<PolygonStruct*> polygons = dataManager->GetAllPolygons();
    for (int i = 0; i < polygons.count(); i++)
    {
        PolygonStruct* polygon = polygons.value(i);
        painter.setPen(Qt::darkGreen);
        int rgb = polygon->GetTraversability() * 2.55;
        painter.setBrush(*new QBrush(*new QColor(rgb, rgb, rgb)));
        painter.drawPolygon(*polygon->GetPolygon(), Qt::WindingFill);
    }

    painter.end();
}

void MapQFrame::DrawNode(Node *node, QColor* color)
{
    QPainter painter(this);
    painter.setPen(*color);
    painter.drawPoint(node->x, node->y);
        painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(StartX, StartY, 5, 5);


        painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(FinishX, FinishY, 5, 5);

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
            NewPointsVector.append(*PolygonPoint);
        }
        if (DeletePolygonMode){
            QVector<PolygonStruct*> polygons = dataManager->GetAllPolygons();
            for (int i = 0; i <polygons.length(); i++){
                QPolygon* polygon = polygons.value(i)->GetPolygon();
                if (polygon->containsPoint(QPoint(ev->x(), ev->y()), Qt::OddEvenFill) == 1){
                    qDebug() << "Find delete";

                    dataManager->TryDeletePolygon(i);

                    repaint();
                    break;
                }


            }
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
    emit ChangeButtons(StartMode, FinishMode, NewPolygonMode, DeletePolygonMode);
}

void MapQFrame::changeFinishMode()
{
    FinishMode=!FinishMode;
    StartMode=false;
    NewPolygonMode=false;
    DeletePolygonMode = false;

    emit ChangeButtons(StartMode, FinishMode, NewPolygonMode, DeletePolygonMode);
}

void MapQFrame::changeNewPolygonMode()
{
    NewPolygonMode=!NewPolygonMode;
    StartMode=false;
    FinishMode=false;
    DeletePolygonMode = false;
    emit ChangeButtons(StartMode, FinishMode, NewPolygonMode, DeletePolygonMode);

    if (NewPolygonMode) //если только включили режим
    {
        NewPointsVector  = *(new QVector<QPoint>); //создаем вектор/массив для точек полигон
    }
    else
    {
        bool addResult;
        PolygonStruct* newPolygon = dataManager->TryCreateNewPolygon(NewPointsVector, addResult);
        newPolygon->SetTraversability(trace_ability);
        if (!addResult)
        {
            //если не создали новый полигон
        }
        repaint();

    }
}

void MapQFrame::changeDeletePolygonMode(){
    DeletePolygonMode = !DeletePolygonMode;
    StartMode = false;
    FinishMode = false;
    NewPolygonMode = false;
    emit ChangeButtons(StartMode, FinishMode, NewPolygonMode, DeletePolygonMode);

}





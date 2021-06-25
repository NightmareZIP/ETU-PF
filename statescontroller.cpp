#include "statescontroller.h"
#include <QtDebug>

StatesController::StatesController(DataManager *dataManager)
{
    this->dataManager = dataManager;
}

StatesController::STATES StatesController::GetCurrentState()
{
    return currentState;
}

void StatesController::SwitchState(STATES newState)
{
    ClearTemporalData();
    currentState = newState;
    emit OnStateChanged(currentState);
}

void StatesController::HandlePressOnMap(int x, int y)
{
    switch (currentState)
    {
        case StatesController::Start:
            HandlePressOnMapWhileInStartState(x, y);
            break;

        case StatesController::End:
            HandlePressOnMapWhileInEndState(x, y);
            break;

        case StatesController::CreatePolygon:
            HandlePressOnMapWhileInCreatePolygonState(x, y);
            break;

        case StatesController::DeletePolygon:
            HandlePressOnMapWhileInDeletePolygonState(x, y);
            break;
    }
}

void StatesController::ClearTemporalData()
{
    dataManager->newPolygonPoints.clear();
    emit OnRepaintRequested();
}

void StatesController::HandlePressOnMapWhileInStartState(int x, int y)
{
    if (dataManager->map->NodeAt(x, y) != dataManager->endNode)
    {
        dataManager->startNode = dataManager->map->NodeAt(x, y);
        qDebug() << "Set START node position at (" << dataManager->startNode->x << "; " << dataManager->startNode->y << ").";
        emit OnRepaintRequested();
    }
    else
    {
        qDebug() << "START node cannot be the same as END node";
    }
}

void StatesController::HandlePressOnMapWhileInEndState(int x, int y)
{
    if (dataManager->map->NodeAt(x, y) != dataManager->startNode)
    {
        dataManager->endNode = dataManager->map->NodeAt(x, y);
        qDebug() << "Set END node position at (" << dataManager->endNode->x << "; " << dataManager->endNode->y << ").";
        emit OnRepaintRequested();
    }
    else
    {
        qDebug() << "END node cannot be the same as START node";
    }
}

void StatesController::HandlePressOnMapWhileInCreatePolygonState(int x, int y)
{
    QPoint* point = new QPoint(x, y);
    dataManager->newPolygonPoints.append(*point);
    delete point;
    qDebug() << "Added point at (" << x << "; " << y << ").";
    emit OnRepaintRequested();
}

void StatesController::HandlePressOnMapWhileInDeletePolygonState(int x, int y)
{
    for (int i = 0; i < dataManager->polygonList.count(); i++)
    {
        PolygonStruct* ps = dataManager->polygonList.value(i);
        QPoint* point = new QPoint(x, y);
        if (ps->GetPolygon()->containsPoint(*point, Qt::WindingFill))
        {
            dataManager->polygonList.removeAt(i);
            qDebug() << "Deleted polygon.";
        }
        delete point;
    }
    emit OnRepaintRequested();
}

void StatesController::TryCreateNewPolygon()
{
    bool actionResult;
    dataManager->TryCreateNewPolygon(dataManager->newPolygonPoints, actionResult);
    dataManager->newPolygonPoints.clear();
    emit OnRepaintRequested();
    if (actionResult)
    {
        qDebug() << "Created new polygon with traversability value of (" << dataManager->polygonList.last()->GetTraversability() << ").";
    }
    else
    {
        qDebug() << "Did not create new polygon";
    }
}

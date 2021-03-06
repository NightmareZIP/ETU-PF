#include "statescontroller.h"
#include <QtDebug>
#include <qelapsedtimer.h>
#include "pathfinder.h"
#include <QFile>
#include <QXmlStreamWriter>

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
    dataManager->lastFoundPath.clear();
    dataManager->lastFoundPathOriginal.clear();
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
    for (int i = dataManager->polygonList.count() - 1; i >= 0; i--)
    {
        PolygonStruct* ps = dataManager->polygonList.value(i);
        QPoint* point = new QPoint(x, y);
        if (ps->GetPolygon()->containsPoint(*point, Qt::WindingFill))
        {
            dataManager->polygonList.removeAt(i);
            delete ps;
            qDebug() << "Deleted polygon.";            
            delete point;
            break;
        }
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

void StatesController::FindPath()
{
    QElapsedTimer timer;
    timer.start();

    QVector<Node*> path;
    Node* startNode = dataManager->startNode;
    Node* endNode = dataManager->endNode;


    if (startNode == nullptr || endNode == nullptr)
    {
        qDebug() << "Cannot find path.";
        return;
    }

    dataManager->BuildMap();
    dataManager->lastFoundPath = Pathfinder::FindPath(startNode, endNode, dataManager->map);    
    dataManager->lastFoundPathOriginal = dataManager->lastFoundPath;

    int foundPathLength = dataManager->lastFoundPath.count();
    if (calculatePulledPath)
    {
        dataManager->ConvertPathToBLine();
    }
    int newPathLength = dataManager->lastFoundPath.count();


    emit OnRepaintRequested();

    writeXMLPath();
    qDebug() << "Found Path(" << foundPathLength << ")->(" << newPathLength << ") in " << timer.elapsed() << "ms.";
}


void StatesController::writeXMLPath()
{
    QString filename = "./pathCoordinates.xml";
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    double time = 0;
// ???????????? ??????????????
    for(Node*& point : dataManager->lastFoundPath)
    {
        time += 100.0 / (point->traversability);
    }
    qDebug() << "XML started" << time;
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Path");

    xmlWriter.writeStartElement("Distance");
    xmlWriter.writeCharacters(QString::number(dataManager->lastFoundPath.size()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Time");
    xmlWriter.writeAttribute("time","seconds");
    xmlWriter.writeCharacters(QString::number(time));
    xmlWriter.writeEndElement();

     xmlWriter.writeStartElement("Points");

    for(auto& point : dataManager->lastFoundPath)
    {
        xmlWriter.writeStartElement("Point");

        xmlWriter.writeStartElement("x");
        xmlWriter.writeCharacters(QString::number(point->x));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("y");
        xmlWriter.writeCharacters(QString::number(point->y));
        xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();

    }

    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

}

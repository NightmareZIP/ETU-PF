#ifndef CONTROLSTATES_H
#define CONTROLSTATES_H

#include <qobject.h>
#include <QPoint>
#include <datamanager.h>

class StatesController : public QObject
{
    Q_OBJECT
public:
    StatesController(DataManager* dataManager);

    enum STATES {Idle, Start, End, CreatePolygon, DeletePolygon};

    bool calculatePulledPath = false;

    STATES GetCurrentState();
    void SwitchState(STATES newState);

    void TryCreateNewPolygon();
    void FindPath();
    void writeXMLPath();

public slots:
    void HandlePressOnMap(int x, int y);

signals:
    void OnStateChanged(STATES newState);
    void OnRepaintRequested();

private:
    DataManager* dataManager;
    STATES currentState;

    void ClearTemporalData();
    void HandlePressOnMapWhileInStartState(int x, int y);
    void HandlePressOnMapWhileInEndState(int x, int y);
    void HandlePressOnMapWhileInCreatePolygonState(int x, int y);
    void HandlePressOnMapWhileInDeletePolygonState(int x, int y);
};

#endif // CONTROLSTATES_H

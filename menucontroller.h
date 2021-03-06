#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <mainwindow.h>
#include <mapqframe.h>
#include <QString>
#include <statescontroller.h>
#include <qstackedwidget.h>
#include <QSpinBox>
#include <QCheckBox>
#include <qradiobutton.h>

class AppController;

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(MainWindow*);
    MapQFrame* GetMapFrame();

    void PrintCursorCoords(QLabel* label, int x, int y);

public slots:
    void HandleStateChange(StatesController::STATES newState);

private:

    QStackedWidget* menuStack;

    //Main Menu tab
    QPushButton* StartButton;
    QPushButton* FinishButton;
    QPushButton* CreatePolygonButton;
    QPushButton* SetTraversabilityButton;
    QPushButton* DeletePolygonButton;
    QPushButton* FindPathButton;
    QRadioButton* OriginalPathRadioBox;
    QRadioButton* PulledPathRadioBox;
    QCheckBox* CalculatePulledPath;
    //----------------------------------

    //Start tab
    QPushButton* BackFromStartPageButton;
    //-----------------------------------

    //End tab
    QPushButton* BackFromEndPageButton;
    //---------------------------------

    //Create Polygon tab
    QSpinBox* TraversabilitySpinBox;
    QPushButton* CreatePolygonActionButton;
    QPushButton* BackFromCreatePolygonPageButton;
    //-------------------------------------------

    //Delete Polygon tab
    QPushButton* BackFromDeletePolygonPage;
    //-------------------------------------

    QLabel* stateLabel;
    QLineEdit* traversabilityLine;

    MapQFrame* mapFrame;
    StatesController* statesController;
    DataManager* dataManager;

    void PrintCurrentState(QLabel* outputLabel, QString stateName);
    void ConnectStateSwitchButton(QPushButton* button, StatesController::STATES state);
};

#endif // MENUCONTROLLER_H

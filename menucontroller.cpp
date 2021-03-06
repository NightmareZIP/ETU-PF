#include "menucontroller.h"
#include "QDebug"

template<typename T>
T* FindChild(MainWindow* w, QString name)
{
   T* obj = w->findChild<T*>(name);
   if (obj == NULL)
   {
        qDebug() << "No object with such name was found. (" << name << ").";
   }
   return obj;
}

void AppController::ConnectStateSwitchButton(QPushButton *button, StatesController::STATES state)
{
    connect(button, &QPushButton::released, [=]
    {
        statesController->SwitchState(state);
    });
}

AppController::AppController(MainWindow* w) : QObject(w)
{
    //поиск элементов
    menuStack               = FindChild<QStackedWidget>(w, "MenuStack");
    StartButton             = FindChild<QPushButton>(w, "StartButton");
    FinishButton            = FindChild<QPushButton>(w, "FinishButton");
    CreatePolygonButton     = FindChild<QPushButton>(w, "CreatePolygonButton");
    SetTraversabilityButton = FindChild<QPushButton>(w, "SetTraversabilityButton");
    DeletePolygonButton     = FindChild<QPushButton>(w, "DeletePolygonButton");
    FindPathButton          = FindChild<QPushButton>(w, "FindPathButton");

    OriginalPathRadioBox = FindChild<QRadioButton>(w, "OriginalPathRadioBox");
    PulledPathRadioBox   = FindChild<QRadioButton>(w, "PulledPathRadioBox");
    CalculatePulledPath  = FindChild<QCheckBox>(w, "CalculatePulledPath");

    BackFromStartPageButton         = FindChild<QPushButton>(w, "BackFromStartPage");
    BackFromEndPageButton           = FindChild<QPushButton>(w, "BackFromEndPage");

    TraversabilitySpinBox           = FindChild<QSpinBox>(w, "TraversabilitySpinBox");
    CreatePolygonActionButton       = FindChild<QPushButton>(w, "CreatePolygonActionButton");
    BackFromCreatePolygonPageButton = FindChild<QPushButton>(w, "BackFromCreatePolygonPage");

    BackFromDeletePolygonPage = FindChild<QPushButton>(w, "BackFromDeletePolygonPage");

    stateLabel         = FindChild<QLabel>(w, "StateLabel");
    traversabilityLine = FindChild<QLineEdit>(w, "TraversabilityLine");
    mapFrame           = FindChild<MapQFrame>(w, "MapFrame");
    //----------------------------------------------

    //привязка ивентов
    ConnectStateSwitchButton(StartButton, StatesController::Start);
    ConnectStateSwitchButton(FinishButton, StatesController::End);
    ConnectStateSwitchButton(CreatePolygonButton, StatesController::CreatePolygon);
    ConnectStateSwitchButton(DeletePolygonButton, StatesController::DeletePolygon);

    connect(OriginalPathRadioBox, &QRadioButton::released, [=]{
       GetMapFrame()->showOriginalPath = true;
       GetMapFrame()->showPulledPath = false;
       GetMapFrame()->Repaint(dataManager);
    });

    connect(PulledPathRadioBox, &QRadioButton::released, [=]{
       GetMapFrame()->showOriginalPath = false;
       GetMapFrame()->showPulledPath = true;
       GetMapFrame()->Repaint(dataManager);
    });

    connect(CalculatePulledPath, &QCheckBox::stateChanged, [=]
    {
       statesController->calculatePulledPath = CalculatePulledPath->checkState() == Qt::CheckState::Checked ? true : false;
    });

    ConnectStateSwitchButton(BackFromStartPageButton, StatesController::Idle);

    ConnectStateSwitchButton(BackFromEndPageButton, StatesController::Idle);

    connect(TraversabilitySpinBox, &QSpinBox::valueChanged, [=]{
        dataManager->newPolygonTraversability = TraversabilitySpinBox->value();
    });
    connect(CreatePolygonActionButton, &QPushButton::released, [=]{
       statesController->TryCreateNewPolygon();
    });
    ConnectStateSwitchButton(BackFromCreatePolygonPageButton, StatesController::Idle);

    ConnectStateSwitchButton(BackFromDeletePolygonPage, StatesController::Idle);

    connect(FindPathButton, &QPushButton::released, [=]{
        statesController->FindPath();
    });
    //-----------------------------------------------------------------

    dataManager = new DataManager();

    //иницилизация недо SM
    statesController = new StatesController(dataManager);
    connect(statesController, &StatesController::OnStateChanged, this, &AppController::HandleStateChange);
    connect(mapFrame, &MapQFrame::OnMousePressed, statesController, &StatesController::HandlePressOnMap);
    connect(statesController, &StatesController::OnRepaintRequested, [=]{
       mapFrame->Repaint(dataManager);
    });
    statesController->SwitchState(StatesController::Idle);
    //----------------------------------------------------
}

void AppController::PrintCursorCoords(QLabel* label, int x, int y)
{
    QString string = "X: " + QString::number(x) + " Y: " + QString::number(y);
    label->setText(string);
}

MapQFrame* AppController::GetMapFrame()
{
    return mapFrame;
}

void AppController::HandleStateChange(StatesController::STATES newState)
{
    switch(newState)
    {
        case StatesController::Idle:
            PrintCurrentState(stateLabel, "Idle State");
            menuStack->setCurrentIndex(0);
        break;

        case StatesController::Start:
            PrintCurrentState(stateLabel, "Start Point State");
            menuStack->setCurrentIndex(1);
        break;

        case StatesController::End:
            PrintCurrentState(stateLabel, "End Point State");
            menuStack->setCurrentIndex(2);
        break;

        case StatesController::CreatePolygon:
            PrintCurrentState(stateLabel, "Create Polygon State");
            menuStack->setCurrentIndex(3);
        break;

        case StatesController::DeletePolygon:
            PrintCurrentState(stateLabel, "Delete Polygon State");
            menuStack->setCurrentIndex(4);
        break;

        default:
            PrintCurrentState(stateLabel, "Unknown State");
    }
}

void AppController::PrintCurrentState(QLabel *outputLabel, QString stateName)
{
    outputLabel->setText(stateName);
}

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

MenuController::MenuController(MainWindow* w) : QObject(w)
{
    //поиск элементов
    _startButton = FindChild<QPushButton>(w, "StartButton");
    _finishButton = FindChild<QPushButton>(w, "FinishButton");
    _newPolygonButton = FindChild<QPushButton>(w, "NewPolygonButton");
    _label1 = FindChild<QLabel>(w, "LogLabel_1");
    _label2 = FindChild<QLabel>(w, "LogLabel_2");
    _label3 = FindChild<QLabel>(w, "LogLabel_3");
    _mapFrame = FindChild<MapQFrame>(w, "MapFrame");

    connect(_startButton, &QPushButton::released, [=]{
        OnStartButtonPressed();
    });
    connect(_finishButton, &QPushButton::released, [=]{
        OnFinishButtonPressed();
    });
    connect(_newPolygonButton, &QPushButton::released, [=]{
        OnNewPolygonButtonPressed();
    });

    //привязка ивентов
    connect(_startButton, &QPushButton::released, _mapFrame, &MapQFrame::changeStartMode);
    connect(_finishButton, &QPushButton::released, _mapFrame, &MapQFrame::changeFinishMode);
    connect(_newPolygonButton, &QPushButton::released, _mapFrame, &MapQFrame::changeNewPolygonMode);

    //закос на FSM
    ExitActionState();
}

void MenuController::PrintCursorCoords(int x, int y)
{
    QString string = "X: " + QString::number(x) + " Y: " + QString::number(y);
    _label3->setText(string);
}

void MenuController::OnMousePressedInsideMapQFrame(int x, int y)
{
    if (_actionFlag)
    {
        PrintCursorCoords(x, y);
    }
    else
    {
       _label3->setText("exit IDLE state first");
    }
}

MapQFrame* MenuController::GetMapFrame()
{
    return _mapFrame;
}

void MenuController::OnStartButtonPressed()
{
    _label1->setText("Start button was pressed.");
    EnterActionState();
}

void MenuController::OnFinishButtonPressed()
{
    _label1->setText("Finish button was pressed.");
    ExitActionState();
}

void MenuController::OnNewPolygonButtonPressed()
{
    _label1->setText("Polygon button was pressed.");
}

void MenuController::EnterActionState()
{
    _actionFlag = true;
    _label2->setText("ACTION STATE");
}

void MenuController::ExitActionState()
{
    _actionFlag = false;
    _label2->setText("IDLE STATE");
}

void MenuController::ButtonsColor(bool stateS, bool stateF, bool stateNP)
{
    if (stateS) _startButton->setStyleSheet("background-color:green");
    else _startButton->setStyleSheet("background-color:grey");

    if (stateF) _finishButton->setStyleSheet("background-color:red");
    else _finishButton->setStyleSheet("background-color:grey");

    if (stateNP) _newPolygonButton->setStyleSheet("background-color:yellow");
    else _newPolygonButton->setStyleSheet("background-color:grey");
}



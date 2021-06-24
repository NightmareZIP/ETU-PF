#include "mainwindow.h"

#include <menucontroller.h>
#include <QApplication>
#include <mapqframe.h>

MenuController* menuController;
MapQFrame* mapFrame;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    menuController = new MenuController(&w);
    mapFrame = menuController->GetMapFrame();

    QObject::connect(mapFrame, &MapQFrame::OnMousePressed, menuController, &MenuController::OnMousePressedInsideMapQFrame);
    QObject::connect(mapFrame, &MapQFrame::ChangeButtons, menuController, &MenuController::ButtonsColor);


    //QObject::connect(menuController, &MenuController::OnStartButtonPressed, mapFrame, &MapQFrame::changeStartMode);
    //QObject::connect(menuController, &MenuController::OnFinishButtonPressed, mapFrame, &MapQFrame::changeFinishMode);

    return a.exec();
}

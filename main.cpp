#include "mainwindow.h"

#include <menucontroller.h>
#include <QApplication>
#include <mapqframe.h>
#include <datamanager.h>

MenuController* menuController;
MapQFrame* mapFrame;
DataManager* dataManager;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    menuController = new MenuController(&w);
    mapFrame = menuController->GetMapFrame();

    dataManager = new DataManager();
    mapFrame->dataManager = dataManager;

    QObject::connect(mapFrame, &MapQFrame::OnMousePressed, menuController, &MenuController::OnMousePressedInsideMapQFrame);
    QObject::connect(mapFrame, &MapQFrame::ChangeButtons, menuController, &MenuController::ButtonsColor);


    //QObject::connect(menuController, &MenuController::OnStartButtonPressed, mapFrame, &MapQFrame::changeStartMode);
    //QObject::connect(menuController, &MenuController::OnFinishButtonPressed, mapFrame, &MapQFrame::changeFinishMode);

    //QObject::connect(menuController, &MenuController::OnStartButtonPressed, mapFrame, &MapQFrame::changeStartMode);
    //QObject::connect(menuController, &MenuController::OnFinishButtonPressed, mapFrame, &MapQFrame::changeFinishMode);

    return a.exec();
}

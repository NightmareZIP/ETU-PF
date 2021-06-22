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

    return a.exec();
}

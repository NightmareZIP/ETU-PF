#include "mainwindow.h"

#include <menucontroller.h>
#include <QApplication>
#include <mapqframe.h>
#include <datamanager.h>

AppController* menuController;
MapQFrame* mapFrame;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    menuController = new AppController(&w);
    mapFrame = menuController->GetMapFrame();    

    return a.exec();
}

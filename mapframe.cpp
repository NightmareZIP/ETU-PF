#include "mapframe.h"

MapFrame::MapFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::MapFrame)
{
    ui->setupUi(this);


    this->setWindowTitle("Path Search");
}

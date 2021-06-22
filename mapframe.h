#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <QFrame>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MapFrame; }
QT_END_NAMESPACE

class MapFrame : public QFrame
{
    Q_OBJECT

public:
    MapFrame(QWidget *parent = nullptr);
    ~MapFrame();

    void mouseMoveEvent(QMouseEvent *ev);

private:
    Ui::MapFrame *ui;
};

#endif // MAPFRAME_H

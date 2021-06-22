#ifndef MAPQFRAME_H
#define MAPQFRAME_H

#include <QFrame>
#include <QMouseEvent>

class MapQFrame;

class MapQFrame : public QFrame
{
    Q_OBJECT
public:
    explicit MapQFrame(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent * ev);
    int x,y;

signals:
    void OnMousePressed(int x, int y);

private:
    void UpdateCoords();
};

#endif // MAPQFRAME_H

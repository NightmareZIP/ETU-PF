#ifndef MAPQFRAME_H
#define MAPQFRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QVector>
#include <QPoint>
#include <datamanager.h>
#include <polygonstruct.h>
#include <QString>

class MapQFrame;

class MapQFrame : public QFrame
{
    Q_OBJECT
public:
    explicit MapQFrame(QWidget *parent = nullptr);   

    void Repaint(DataManager* dataManager);
    void mousePressEvent(QMouseEvent * ev);

    bool showPulledPath = false;
    bool showOriginalPath = true;

signals:
    void OnMousePressed(int x, int y);
    void ChangeButtons (bool s, bool s2, bool s3, bool s4);

private:
    void UpdateCoords();
    void paintEvent(QPaintEvent *event);

    void DrawCircle(QPainter& painter, int x, int y, QColor color, int size = 3);
    void DrawPolygons(QPainter& painter);
    void DrawNode(Node *node, QColor* color);

    DataManager* dataManager = nullptr;
};


#endif // MAPQFRAME_H

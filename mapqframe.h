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

    DataManager* dataManager;

    void mousePressEvent(QMouseEvent * ev);
    void changeStartMode();
    void changeFinishMode();
    void changeNewPolygonMode();
    void changeDeletePolygonMode();
    int x,y;
    int trace_ability;
    bool StartMode = false, FinishMode = false, NewPolygonMode = false,
    DeletePolygonMode = false;
    int StartX, StartY, FinishX, FinishY;

signals:
    void OnMousePressed(int x, int y);
    void ChangeButtons (bool s, bool s2, bool s3, bool s4);



private:
    void UpdateCoords();
    void paintEvent(QPaintEvent *event);

    void DrawPolygons();
    void DrawNode(Node *node, QColor* color);

    QVector<QPoint> NewPointsVector;
};


#endif // MAPQFRAME_H

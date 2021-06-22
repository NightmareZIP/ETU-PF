#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <mainwindow.h>
#include <mapqframe.h>

class MenuController;

class MenuController : public QObject
{
    Q_OBJECT
public:
    explicit MenuController(MainWindow*);
    MapQFrame* GetMapFrame();

    void PrintCursorCoords(int x, int y);

public slots:
    void OnMousePressedInsideMapQFrame(int x, int y);

private:
    QPushButton* _startButton;
    QPushButton* _finishButton;

    QLabel* _label1;
    QLabel* _label2;
    QLabel* _label3;

    MapQFrame* _mapFrame;

    bool _actionFlag;

    void OnStartButtonPressed();
    void OnFinishButtonPressed();

    void EnterActionState();
    void ExitActionState();
};

#endif // MENUCONTROLLER_H

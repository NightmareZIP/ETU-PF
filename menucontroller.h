#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
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
    void OnStartButtonPressed();
    void OnFinishButtonPressed();
    void OnNewPolygonButtonPressed();
    void OnSetTraceButtonPressed();
    void ButtonsColor(bool s, bool s2, bool s3);

private:
    QPushButton* _startButton;
    QPushButton* _finishButton;
    QPushButton* _newPolygonButton;
    QPushButton* _SetTraceButton;


    QLabel* _label1;
    QLabel* _label2;
    QLabel* _label3;

    QLineEdit* _LineEdit;

    MapQFrame* _mapFrame;

    bool _actionFlag;

    void EnterActionState();
    void ExitActionState();
};

#endif // MENUCONTROLLER_H

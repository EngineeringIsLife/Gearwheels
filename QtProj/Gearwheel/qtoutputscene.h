#ifndef QTOUTPUTSCENE_H
#define QTOUTPUTSCENE_H

#include "zahnradmath.h"
#include <iostream>
#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QTimer>

// View
class GearwheelOutputView : public QGraphicsView
{
    Q_OBJECT

private:
    QWidget* parent;
    ProfilMathematisch* gearwheel;

    QTimer* rotationtimer;

    int posx, posy;
    int startx, starty;
    int stepsize;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void keyPressEvent(QKeyEvent *event);

    void createTimer(void)
    {
        rotationtimer = new QTimer(this);
        connect(rotationtimer, SIGNAL(timeout()), this, SLOT(rotationTimerEvent()));
    }

public:

    explicit GearwheelOutputView(QWidget *parent = 0)
        : QGraphicsView(parent), parent(parent), gearwheel(0) { posx = 200; posy = 200; stepsize = 100; createTimer(); }

    explicit GearwheelOutputView(QWidget *parent, ProfilMathematisch* zahnrad)
        : QGraphicsView(parent), parent(parent), gearwheel(zahnrad)
    { posx = 200; posy = 200; stepsize = 100; createTimer(); }

    ~GearwheelOutputView(void)
    { delete rotationtimer; }

public:

public slots:
    void rotationTimerEvent(void)
    {
        emit rotateFull();
    }

    void toggleRotation()
    {
        if (rotationtimer->isActive()) rotationtimer->stop();
        else rotationtimer->start(stepsize);
    }

    void speedSliderChanged(int x)
    {
        emit changeSpeed((float)x);
    }

    void changeSteps(int x)
    {
        std::cout << x << std::endl;
        stepsize = (x+1)*10;
        rotationtimer->setInterval(stepsize);
    }

signals:
    void changePosition(int x, int y);
    void zoomIn();
    void zoomOut();
    void rotateFine();
    void rotateFull();
    void changeSpeed(float x);
};

#endif // QTOUTPUTSCENE_H

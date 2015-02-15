#ifndef QTOUTPUTSCENE_H
#define QTOUTPUTSCENE_H

#include "zahnradmath.h"

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
        : QGraphicsView(parent), parent(parent), gearwheel(0) { posx = 200; posy = 200; createTimer(); }

    explicit GearwheelOutputView(QWidget *parent, ProfilMathematisch* zahnrad)
        : QGraphicsView(parent), parent(parent), gearwheel(zahnrad)
    { posx = 200; posy = 200; createTimer(); }

    ~GearwheelOutputView(void)
    { delete rotationtimer;  }

public:

public slots:
    void rotationTimerEvent(void)
    {
        emit rotateFull();
    }

    void toggleRotation()
    {
        if (rotationtimer->isActive()) rotationtimer->stop();
        else rotationtimer->start(100);
    }

signals:
    void changePosition(int x, int y);
    void zoomIn();
    void zoomOut();
    void rotateFine();
    void rotateFull();
};

#endif // QTOUTPUTSCENE_H

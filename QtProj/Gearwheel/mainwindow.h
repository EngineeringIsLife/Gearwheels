#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>

#include "zahnradmath.h"
#include "gearwheeloutput.h"
#include "qtoutputcontroller.h"
#include "qtoutputscene.h"

/*
class GraphicView : public QGraphicsView
{
public:
    int posx, posy;

    explicit GraphicView(QWidget *parent = 0)
        : QGraphicsView(parent) { }
    virtual void mouseMoveEvent(QMouseEvent *ev);
};*/

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    GearwheelOutputController* controller;

    //GearwheelOutputScene *scene;
    //GearwheelOutputController *outcontroller;
    //QTimer *timer;
    //GearwheelItem *gearwheelitem;
    //GraphicView *outputZone;
    //GearwheelOutputController *gwoutctrl;

    //bool rotationStarted;
    //float zoom;
    //float angle;

    //virtual void keyPressEvent(QKeyEvent *ev);
    //virtual void mousePressEvent(QMouseEvent *ev);  // Replace with wheelEvent

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void toggleRotation(void);
    void rotationTimerEvent(void);
};

#endif // MAINWINDOW_H

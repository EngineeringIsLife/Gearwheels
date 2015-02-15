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

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    GearwheelOutputView* view;
    GearwheelOutputController* controller;

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWINDOW_H

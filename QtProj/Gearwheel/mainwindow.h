#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>

#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QGridLayout>

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>

#include "mainlayout.h"

#include "zahnradmath.h"
#include "gearwheeloutput.h"
#include "qtoutputcontroller.h"
#include "qtoutputview.h"



class MainWidget : public QWidget
{
    Q_OBJECT

private:
    GearwheelOutputView* view;
    GearwheelOutputController* controller;

    MainLayout* mainlayout;

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWINDOW_H

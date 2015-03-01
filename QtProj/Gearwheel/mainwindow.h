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

#include "zahnradmath.h"
#include "gearwheeloutput.h"
#include "qtoutputcontroller.h"
#include "qtoutputscene.h"

class MainLayout// : public QWidget
{
private:
    // Layout-Items
    QVBoxLayout* layout_main;
    //QGridLayout* layout_main;
    QGroupBox* box_title;
    QGroupBox* box_buttons;
    QGroupBox* box_status;
    QLabel* label_title;
    QHBoxLayout* layout_buttons;
    QHBoxLayout* layout_output;
    QLabel* label_testtext;
    QHBoxLayout* layout_status;
    QLabel* label_status;

    void createToplevelLayout(QWidget *parent = 0)
    {
        layout_main = new QVBoxLayout(parent);
        //layout_main = new QGridLayout(parent);

        box_title = new QGroupBox(parent);
        layout_main->addWidget(box_title);
        createTitleFrame();

        box_buttons = new QGroupBox(parent);
        layout_main->addWidget(box_buttons);
        createButtonsFrame();

        box_output = new QGroupBox(parent);
        layout_main->addWidget(box_output);
        createOutputFrame();

        box_status = new QGroupBox(parent);
        layout_main->addWidget(box_status);
        createStatusFrame();
    }

    void createTitleFrame(void)
    {
        // First frame - Title
        label_title = new QLabel(box_title);
        label_title->setText("Gearwheel Visualization");
    }

    void createButtonsFrame(void)
    {
        // Second frame - Buttons
        layout_buttons = new QHBoxLayout(box_buttons);

        rotateButton = new QPushButton("Rotate");
        secondGWButton = new QPushButton("Second Gearwheel");
        exitButton = new QPushButton("Exit");

        layout_buttons->addWidget(rotateButton);
        layout_buttons->addWidget(secondGWButton);
        layout_buttons->addWidget(exitButton);
    }

    void createOutputFrame(void)
    {
        // Third frame - In-/Output
        layout_output = new QHBoxLayout(box_output);

        label_testtext = new QLabel(box_output);
        label_testtext->setText("Gearwheel");

        slider_rotspeed = new QSlider(Qt::Horizontal, box_output);
        slider_rotsteps = new QSlider(Qt::Horizontal, box_output);

        layout_output->addWidget(label_testtext);
        layout_output->addWidget(slider_rotspeed);
        layout_output->addWidget(slider_rotsteps);
    }

    void createStatusFrame(void)
    {
        // Fourth frame - Status bar
        layout_status = new QHBoxLayout(box_status);

        label_status = new QLabel(box_status);
        label_status->setText("Ready");

        layout_status->addWidget(label_status);
    }

public:
    QGroupBox* box_output;

    QPushButton* rotateButton;
    QPushButton* secondGWButton;
    QPushButton* exitButton;
    QSlider* slider_rotspeed;
    QSlider* slider_rotsteps;

    MainLayout(QWidget *parent = 0);
    ~MainLayout(void);
    void addView(QGraphicsView *view);
};

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    GearwheelOutputView* view;
    GearwheelOutputController* controller;

    MainLayout mainlayout;

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWINDOW_H

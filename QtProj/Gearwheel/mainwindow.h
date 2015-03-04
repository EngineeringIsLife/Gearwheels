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

#include "zahnradmath.h"
#include "gearwheeloutput.h"
#include "qtoutputcontroller.h"
#include "qtoutputscene.h"

class MainLayout
{
private:
    QWidget* parent;
    // Layout-Items
    QGridLayout* layout_main;
    QGroupBox* box_buttons;
    QGroupBox* box_output;
    QLabel* label_title;
    QHBoxLayout* layout_buttons;
    QVBoxLayout* layout_output;
    QLabel* label_testtext;
    QLabel* label_status;

    void createToplevelLayout(QWidget *parent = 0)
    {
        layout_main = new QGridLayout(parent);

        createTitleFrame();
        createButtonsFrame();
        createOutputFrame();
        createStatusFrame();
    }

    void createTitleFrame(void)
    {
        // First frame - Title
        label_title = new QLabel();
        layout_main->addWidget(label_title, 1, 1, 1, 2);
        label_title->setText("Gearwheel Visualization");
    }

    void createButtonsFrame(void)
    {
        // Second frame - Buttons
        box_buttons = new QGroupBox(parent);
        layout_main->addWidget(box_buttons, 2, 1, 1, 2);
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
        // Third frame - Inputs for gearwheel
        box_output = new QGroupBox(parent);
        layout_main->addWidget(box_output, 3, 1, 1, 1);
        layout_output = new QVBoxLayout(box_output);

        label_testtext = new QLabel(box_output);
        label_testtext->setText("Gearwheel");
        layout_output->addWidget(label_testtext);

        QLabel* label_toothcount1 = new QLabel("Gearwheel 1 - Nr of tooth");
        layout_output->addWidget(label_toothcount1);
        output_toothcountspinner = new QSpinBox(box_output);
        output_toothcountspinner->setRange(4,100);
        layout_output->addWidget(output_toothcountspinner);

        QLabel* label_toothcount2 = new QLabel("Gearwheel 2 - Nr of tooth");
        layout_output->addWidget(label_toothcount2);
        output_toothcount2spinner = new QSpinBox(box_output);
        output_toothcount2spinner->setRange(4,100);
        layout_output->addWidget(output_toothcount2spinner);

        output_diametercheckbox = new QCheckBox("Show diameter", box_output);
        layout_output->addWidget(output_diametercheckbox);
        output_footdiametercheckbox = new QCheckBox("Show foot diameter", box_output);
        layout_output->addWidget(output_footdiametercheckbox);
        output_outerdiametercheckbox = new QCheckBox("Show outer diameter", box_output);
        layout_output->addWidget(output_outerdiametercheckbox);
        output_basediametercheckbox = new QCheckBox("Show base diameter", box_output);
        layout_output->addWidget(output_basediametercheckbox);

        QLabel* label_xmovement = new QLabel("Profilverschiebung");
        layout_output->addWidget(label_xmovement);
        output_xspinner = new QDoubleSpinBox(box_output);
        output_xspinner->setRange(-1.0, 1.0);
        output_xspinner->setSingleStep(0.1);
        layout_output->addWidget(output_xspinner);

        slider_rotspeed = new QSlider(Qt::Horizontal, box_output);
        layout_output->addWidget(slider_rotspeed);

        slider_rotsteps = new QSlider(Qt::Horizontal, box_output);
        layout_output->addWidget(slider_rotsteps);
    }

    void createStatusFrame(void)
    {
        // Fourth frame - Status bar
        label_status = new QLabel();
        label_status->setText("Ready");

        layout_main->addWidget(label_status, 4, 1, 1, 2);
    }

public:
    QPushButton* rotateButton;
    QPushButton* secondGWButton;
    QPushButton* exitButton;
    QSlider* slider_rotspeed;
    QSlider* slider_rotsteps;
    QSpinBox* output_toothcountspinner;
    QSpinBox* output_toothcount2spinner;
    QDoubleSpinBox* output_xspinner;
    QCheckBox* output_diametercheckbox;
    QCheckBox* output_footdiametercheckbox;
    QCheckBox* output_outerdiametercheckbox;
    QCheckBox* output_basediametercheckbox;

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

#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

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

//#include "zahnradmath.h"
//#include "gearwheeloutput.h"
#include "qtoutputscene.h"

class MainLayout : public QObject
{
    Q_OBJECT

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

        gearwheelRotationState(false);
        secondGWVisibility(false);
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

        rotateButton = new QPushButton(box_buttons);//"Rotatieren");
        secondGWButton = new QPushButton(box_buttons); //"Zweites Zahnrad");
        exitButton = new QPushButton("Beenden");

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

        QLabel* label_toothcount1 = new QLabel("Zahnrad 1 - Zähnezahl");
        layout_output->addWidget(label_toothcount1);
        output_toothcountspinner = new QSpinBox(box_output);
        output_toothcountspinner->setRange(4,100);
        layout_output->addWidget(output_toothcountspinner);

        QLabel* label_toothcount2 = new QLabel("Zahnrad 2 - Zähnezahl");
        layout_output->addWidget(label_toothcount2);
        output_toothcount2spinner = new QSpinBox(box_output);
        output_toothcount2spinner->setRange(4,100);
        layout_output->addWidget(output_toothcount2spinner);

        output_diametercheckbox = new QCheckBox("Zeige Durchmesser", box_output);
        layout_output->addWidget(output_diametercheckbox);
        output_footdiametercheckbox = new QCheckBox("Zeige Fußkreisdurchmesser", box_output);
        layout_output->addWidget(output_footdiametercheckbox);
        output_outerdiametercheckbox = new QCheckBox("Zeige Außendurchmesser", box_output);
        layout_output->addWidget(output_outerdiametercheckbox);
        output_basediametercheckbox = new QCheckBox("Zeige Basiskreis", box_output);
        layout_output->addWidget(output_basediametercheckbox);

        QLabel* label_xmovement = new QLabel("Profilverschiebung");
        layout_output->addWidget(label_xmovement);
        output_xspinner = new QDoubleSpinBox(box_output);
        output_xspinner->setRange(-1.0, 1.0);
        output_xspinner->setSingleStep(0.1);
        layout_output->addWidget(output_xspinner);

        QLabel* label_rotspeed = new QLabel("Rotationsgeschwindigkeit");
        layout_output->addWidget(label_rotspeed);
        slider_rotspeed = new QSlider(Qt::Horizontal, box_output);
        layout_output->addWidget(slider_rotspeed);

        QLabel* label_rotdetail = new QLabel("Rechenschrittweite");
        layout_output->addWidget(label_rotdetail);
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
    void changeStatusText(QString newText);
    void changeRotButtonText(QString newText);
    void changeSecGWButtonText(QString newText);

public slots:
    void gearwheelRotationState(bool state);
    void secondGWVisibility(bool state);
};

#endif // MAINLAYOUT_H

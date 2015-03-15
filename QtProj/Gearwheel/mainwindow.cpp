#include "mainwindow.h"
#include <qpainter.h>
#include <iostream>
#include <QMouseEvent>
#include <QTimer>

#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QImage>

#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QSlider>

#include "zahnradfertigung.h"
#include "zahnradmath.h"
#include "gearwheeloutput.h"

#include "qtoutputscene.h"

using namespace std;

Zahnraddaten zahnraddaten(20, .38, .25, 4.0, 0, 0, 15); // Daten eines Zahnrads
ProfilMathematisch zahnrad(zahnraddaten, 50); // Klasse zur Berechnung des Zahnradprofils
GearwheelOutputQt zahnradoutput(zahnrad.zahnprofil); // Hilfsklasse zum Zeichnen eines Zahnrads

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Gearwheels");

    mainlayout = new MainLayout(this);
    view = new GearwheelOutputView(this);
    mainlayout->addView(view);

    controller = new GearwheelOutputController(this, view, mainlayout, &zahnrad);

    view->adjustSize();

    mainlayout->output_toothcountspinner->setValue(zahnraddaten.z());
    mainlayout->output_toothcount2spinner->setValue(zahnraddaten.z());


    // Connections
    connect(mainlayout->slider_rotspeed, SIGNAL(valueChanged(int)), controller, SLOT(changeSpeed(int)));
    connect(mainlayout->slider_rotsteps, SIGNAL(valueChanged(int)), controller, SLOT(changeSteps(int)));

    connect(mainlayout->rotateButton, SIGNAL(clicked()), controller, SLOT(toggleRotation()));
    connect(mainlayout->secondGWButton, SIGNAL(clicked()), controller, SLOT(toggleSecondGearwheel()));
    connect(mainlayout->centerGWButton, SIGNAL(clicked()), controller, SLOT(centerGearwheel()));
    connect(mainlayout->exitButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(mainlayout->output_toothcountspinner, SIGNAL(valueChanged(int)), controller, SLOT(changeToothcount(int)));
    connect(mainlayout->output_toothcount2spinner, SIGNAL(valueChanged(int)), controller, SLOT(changeToothcount2(int)));
    connect(mainlayout->output_xspinner, SIGNAL(valueChanged(double)), controller, SLOT(changeX(double)));
    connect(mainlayout->output_diametercheckbox, SIGNAL(stateChanged(int)), controller, SLOT(setDiameterVisibility(int)));
    connect(mainlayout->output_footdiametercheckbox, SIGNAL(stateChanged(int)), controller, SLOT(setFootdiameterVisibility(int)));
    connect(mainlayout->output_outerdiametercheckbox, SIGNAL(stateChanged(int)), controller, SLOT(setOuterdiameterVisibility(int)));
    connect(mainlayout->output_basediametercheckbox, SIGNAL(stateChanged(int)), controller, SLOT(setBasediameterVisibility(int)));

    connect(controller, SIGNAL(rotationStateChanged(bool)), mainlayout, SLOT(gearwheelRotationState(bool)));
    connect(controller, SIGNAL(secondGearwheelVisChanged(bool)), mainlayout, SLOT(secondGWVisibility(bool)));

    mainlayout->slider_rotspeed->setSliderPosition(50);
    mainlayout->slider_rotsteps->setSliderPosition(20);
    controller->changeSpeed(50);
    controller->changeSteps(20);
}

MainWidget::~MainWidget()
{
    delete view;
    delete controller;
}

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

    QVBoxLayout* layout_main = new QVBoxLayout(this);

    QGroupBox* box_title = new QGroupBox(this);
    QGroupBox* box_buttons = new QGroupBox(this);
    QGroupBox* box_output = new QGroupBox(this);
    QGroupBox* box_status = new QGroupBox(this);

    layout_main->addWidget(box_title);
    layout_main->addWidget(box_buttons);
    layout_main->addWidget(box_output);
    layout_main->addWidget(box_status);

    // First frame - Title
    QLabel* label_title = new QLabel(box_title);
    label_title->setText("Gearwheel Visualization");
    //box_title->setStyle(QStyle());

    // Second frame - Buttons
    QHBoxLayout* layout_buttons = new QHBoxLayout(box_buttons);

    QPushButton *rotateButton = new QPushButton("Rotate");
    QPushButton *secondGWButton = new QPushButton("Second Gearwheel");
    QPushButton *exitButton = new QPushButton("Exit");

    layout_buttons->addWidget(rotateButton);
    layout_buttons->addWidget(secondGWButton);
    layout_buttons->addWidget(exitButton);

    // Third frame - In-/Output
    QHBoxLayout* layout_output = new QHBoxLayout(box_output);

    QLabel* label_testtext = new QLabel(box_output);
    label_testtext->setText("Gearwheel");

    QSlider* slider_rotspeed = new QSlider(Qt::Horizontal, box_output);
    QSlider* slider_rotsteps = new QSlider(Qt::Horizontal, box_output);

    view = new GearwheelOutputView(box_output);
    controller = new GearwheelOutputController(box_output, view, &zahnrad);
    layout_output->addWidget(label_testtext);
    layout_output->addWidget(slider_rotspeed);
    layout_output->addWidget(slider_rotsteps);
    layout_output->addWidget(view);
    view->adjustSize();

    // Fourth frame - Status bar
    QHBoxLayout* layout_status = new QHBoxLayout(box_status);

    QLabel* label_status = new QLabel(box_status);
    label_status->setText("Ready");

    layout_status->addWidget(label_status);


    // Connections
    connect(slider_rotspeed, SIGNAL(valueChanged(int)), controller, SLOT(changeSpeed(int)));
    connect(slider_rotsteps, SIGNAL(valueChanged(int)), controller, SLOT(changeSteps(int)));
    connect(rotateButton, SIGNAL(clicked()), controller, SLOT(toggleRotation()));
    connect(secondGWButton, SIGNAL(clicked()), controller, SLOT(toggleSecondGearwheel()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

MainWidget::~MainWidget()
{
    delete view;
    delete controller;
}

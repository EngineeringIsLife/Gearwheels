#include "mainwindow.h"
#include <qpainter.h>
#include <iostream>
#include <QMouseEvent>
#include <QTimer>

#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QImage>

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

    QPushButton *rotateButton = new QPushButton("Rotate");
    QPushButton *secondGWButton = new QPushButton("Second Gearwheel");
    QPushButton *exitButton = new QPushButton("Exit");

    view = new GearwheelOutputView(this, &zahnrad);
    controller = new GearwheelOutputController(this, view, &zahnrad);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(rotateButton);
    layout->addWidget(secondGWButton);
    layout->addWidget(exitButton);
    layout->addWidget(view);

    connect(rotateButton, SIGNAL(clicked()), view, SLOT(toggleRotation()));
    connect(secondGWButton, SIGNAL(clicked()), controller, SLOT(toggleSecondGearwheel()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

MainWidget::~MainWidget()
{
    delete view;
    delete controller;
}

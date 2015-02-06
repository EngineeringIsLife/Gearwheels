#include "mainwindow.h"
//#include "ui_mainwindow.h"
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

using namespace std;

Zahnraddaten zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 15);
Zahnraddaten zahnrad2(20, .38, .25, 2.0, 0.0, 0.0, 25);
ProfilMathematisch zahn1(zahnrad, 100);
ProfilMathematisch zahn2(zahnrad2, 100);
GearwheelOutputQt output(zahn1.zahnprofil);
GearwheelOutputQt output2(zahn2.zahnprofil);


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    rotationStarted = false;
    zoom = 5.0;
    angle = 1.0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotationTimer()));

    this->setWindowTitle("Gearwheels");

    QPushButton *rotateButton = new QPushButton("&Rotate");
    QPushButton *exitButton = new QPushButton("&Exit");
    QGraphicsView *outputZone = new QGraphicsView(this);

    scene = new QGraphicsScene(this);
    outputZone->setScene(scene);
    outputZone->setBaseSize(300,300);   // TODO: Passenden Befehl finden

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(rotateButton);
    layout->addWidget(exitButton);
    layout->addWidget(outputZone);

    connect(rotateButton, SIGNAL(clicked()), this, SLOT(toggleRotation()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

    zahn1.rotateGearwheel(90);
    zahn2.rotateGearwheel(90);
    zahn2.zahnprofil.mirror();

    output.printToDisplay(*scene, 0, 0, 5);
}

MainWidget::~MainWidget()
{

}

void MainWidget::keyPressEvent(QKeyEvent *ev)
{
    updateGearwheel();
    update();
}

void MainWidget::updateGearwheel(void)
{
    zahn1.rotateGearwheel(angle);
    zahn2.rotateGearwheel(-angle * zahnrad.z / zahnrad2.z);

    //scene->addRect(posi,10,posi+10,10,QPen(Qt::black),QBrush());
}

//void MainWindow::wheelEvent(QWheelEvent *ev)
void MainWidget::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        zoom += 0.1;
    else if(ev->button() == Qt::RightButton)
        zoom -= 0.1;
    update();
}


void MainWidget::toggleRotation(void)
{
    rotationStarted = !rotationStarted;

    if (rotationStarted)
        timer->start(1000);
    else
        timer->stop();
}

void MainWidget::rotationTimer(void)
{
    if (rotationStarted)
        updateGearwheel();
}

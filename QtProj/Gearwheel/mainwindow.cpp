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

QTimer* rotationtimer;

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Gearwheels");

    QPushButton *rotateButton = new QPushButton("Rotate");
    QPushButton *secondGWButton = new QPushButton("Second Gearwheel");
    QPushButton *exitButton = new QPushButton("Exit");

    GearwheelOutputView* view = new GearwheelOutputView(this, &zahnrad);
    controller = new GearwheelOutputController(this, view, &zahnrad);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(rotateButton);
    layout->addWidget(secondGWButton);
    layout->addWidget(exitButton);
    layout->addWidget(view);

    rotationtimer = new QTimer(this);

    connect(rotateButton, SIGNAL(clicked()), this, SLOT(toggleRotation()));
    connect(secondGWButton, SIGNAL(clicked()), controller, SLOT(toggleSecondGearwheel()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(rotationtimer, SIGNAL(timeout()), this, SLOT(rotationTimerEvent()));

    connect(view, SIGNAL(changedView()), controller, SLOT(updateData()));
    connect(view, SIGNAL(changePosition(int,int)), controller, SLOT(moveItem(int,int)));
    connect(view, SIGNAL(zoomIn()), controller, SLOT(zoomItemIn()));
    connect(view, SIGNAL(zoomOut()), controller, SLOT(zoomItemOut()));
    connect(view, SIGNAL(rotateFine()), controller, SLOT(rotateSingle()));

}

MainWidget::~MainWidget()
{
    delete controller;
}

void MainWidget::toggleRotation(void)
{
    controller->toggleRotation();
    if (rotationtimer->isActive()) rotationtimer->stop();
    else rotationtimer->start(100);
}

void MainWidget::rotationTimerEvent(void)
{
    controller->rotate_fwd();
}


/*
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

    //zahn1.rotateGearwheel(90);
    //zahn2.rotateGearwheel(90);
    //zahn2.zahnprofil.mirror();

    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(rotationTimer()));

    this->setWindowTitle("Gearwheels");

    QPushButton *rotateButton = new QPushButton("&Rotate");
    QPushButton *exitButton = new QPushButton("&Exit");
    outputZone = new GraphicView(this);

    outputZone->posx = 200;
    outputZone->posy = 200;

    scene = new GearwheelOutputScene(this, output);
    outcontroller = new GearwheelOutputController(*scene, zahn1);
    outputZone->setScene(scene);
    //outputZone->adjustSize();

    //QBrush* backbrush = new QBrush(Qt::white, Qt::SolidPattern);
    //scene->setBackgroundBrush(*backbrush);
    //gearwheelitem = new GearwheelItem(output, 500-outputZone->posx, 500-outputZone->posy, zoom);
    //gearwheelitem->setScale(1);
    //scene->addItem(gearwheelitem);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(rotateButton);
    layout->addWidget(exitButton);
    layout->addWidget(outputZone);

    //gwoutctrl = new GearwheelOutputController(zahn1);
    connect(rotateButton, SIGNAL(clicked()), this, SLOT(toggleRotation()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

MainWidget::~MainWidget()
{
    delete scene;
//    delete timer;
//    delete gearwheelitem;
    delete outcontroller;
    delete outputZone;
}

void MainWidget::keyPressEvent(QKeyEvent *ev)
{
    outcontroller->rotate();
    update();
}

//void MainWindow::wheelEvent(QWheelEvent *ev)
void MainWidget::mousePressEvent(QMouseEvent *ev)
{
    if (ev->modifiers().testFlag(Qt::ControlModifier))
        return;
    else if (ev->button() == Qt::LeftButton)
        zoom += 0.1;
    else if(ev->button() == Qt::RightButton)
        zoom -= 0.1;
    update();
}

void GraphicView::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton && ev->modifiers().testFlag(Qt::ControlModifier))
    {
        QPointF pos = ev->localPos();
        posx = pos.x();
        posy = pos.y();
        update();
    }
}


void MainWidget::toggleRotation(void)
{
    //gwoutctrl->toggleRotation();
    rotationStarted = !rotationStarted;

    //if (rotationStarted)
//        timer->start(10);
//    else
//        timer->stop();
}
*/

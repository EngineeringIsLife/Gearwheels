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

    zahn1.rotateGearwheel(90);
    zahn2.rotateGearwheel(90);
    zahn2.zahnprofil.mirror();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotationTimer()));

    this->setWindowTitle("Gearwheels");

    QPushButton *rotateButton = new QPushButton("&Rotate");
    QPushButton *exitButton = new QPushButton("&Exit");
    outputZone = new GraphicView(this);

    outputZone->posx = 200;
    outputZone->posy = 200;

    scene = new QGraphicsScene(this);
    QBrush* backbrush = new QBrush(Qt::white, Qt::SolidPattern);
    scene->setBackgroundBrush(*backbrush);
    outputZone->setScene(scene);
    //outputZone->setBaseSize(300,300);   // TODO: Passenden Befehl finden

    gearwheelitem = new GearwheelItem(output, 500-outputZone->posx, 500-outputZone->posy, zoom);
    gearwheelitem->setScale(1);
    scene->addItem(gearwheelitem);
    outputZone->adjustSize();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(rotateButton);
    layout->addWidget(exitButton);
    layout->addWidget(outputZone);

    connect(rotateButton, SIGNAL(clicked()), this, SLOT(toggleRotation()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));



    //output.printToDisplay(*scene, 0, 0, 5);



    //output.printProfile(std::cout);

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
    //zahn1.rotateGearwheel(angle);
    //zahn2.rotateGearwheel(-angle * zahnrad.z / zahnrad2.z);

    zahn1.rotateGearwheel(angle);
    scene->removeItem(gearwheelitem);
    delete gearwheelitem;
    gearwheelitem = new GearwheelItem(output, 500-outputZone->posx, 500-outputZone->posy, zoom);
    scene->addItem(gearwheelitem);
//    output.printToDisplay(scene, 50,50,zoom);
    //gearwheelitem->setRotation(gearwheelitem->rotation() + 1);
    outputZone->update();
}

//void MainWindow::wheelEvent(QWheelEvent *ev)
void MainWidget::mousePressEvent(QMouseEvent *ev)
{
    if (ev->modifiers().testFlag(Qt::ControlModifier))
        return;
    else if (ev->button() == Qt::LeftButton)
        //gearwheelitem->setScale(gearwheelitem->scale() + 0.1);
        zoom += 0.1;
    else if(ev->button() == Qt::RightButton)
        //gearwheelitem->setScale(gearwheelitem->scale() - 0.1);
        zoom -= 0.1;
    std::cout << zoom << std::endl;
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
        //std::cout << "Mouse move event: " << pos.x() << " " << pos.y() << std::endl;
    }
}


void MainWidget::toggleRotation(void)
{
    rotationStarted = !rotationStarted;

    if (rotationStarted)
        timer->start(10);
    else
        timer->stop();
}

void MainWidget::rotationTimer(void)
{
    if (rotationStarted)
        updateGearwheel();
}

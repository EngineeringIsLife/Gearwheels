#include "qtoutputcontroller.h"
#include <math.h>

GearwheelOutputController::GearwheelOutputController(QObject *parent, GearwheelOutputView* view, MainLayout* mainlayout, ProfilMathematisch* zahnrad)
    : QObject(parent), view(view), mainlayout(mainlayout), gearwheel(zahnrad)
{
    posx = 250;
    posy = 250;
    zoomfactor = 5;
    stepsize = 100;
    rot_vel = 0.5;
    rotationdiff = 0;
    rotationpos = 0;
    updateRotationspeed();

    visibility.secondGearwheel = false;
    visibility.diameter = false;
    visibility.diameter_base = false;
    visibility.diameter_foot = false;
    visibility.diameter_outer = false;

    rotating = false;
    scene = new QGraphicsScene(view);
    scene->setSceneRect(-600,-600,600,600);
    outputobj = new GearwheelOutputQt(gearwheel->zahnprofil);
    gearwheelitem = new GearwheelItem(*outputobj, posx, posy, zoomfactor);
    scene->addItem(gearwheelitem);
    view->setScene(scene);
    //view->adjustSize();

    createTimer();
    createSecondGearwheel();
    setConnections();
}

GearwheelOutputController::~GearwheelOutputController(void) {
    delete scene;
    delete outputobj;
    delete outputobj2;
    delete gearwheel2;
    delete gearwheelitem;
    delete gearwheelitem2;
    delete rotationtimer;
}

void GearwheelOutputController::repaintItem(void)
{
    scene->removeItem(gearwheelitem);
    if (visibility.secondGearwheel)
        scene->removeItem(gearwheelitem2);
    scene->clear();
    delete gearwheelitem;
    gearwheelitem = new GearwheelItem(*outputobj, posx, posy, zoomfactor);
    scene->addItem(gearwheelitem);

    float achsabstand = (gearwheel->getDiameter() + gearwheel2->getDiameter())/2*zoomfactor;
    float corner_x = -600 + posx;
    float corner_y = -600 + posy;

    if (visibility.diameter) {
        scene->addEllipse(corner_x-gearwheel->getDiameter()/2*zoomfactor, corner_y-gearwheel->getDiameter()/2*zoomfactor, gearwheel->getDiameter()*zoomfactor, gearwheel->getDiameter()*zoomfactor);
        if (visibility.secondGearwheel) {
            scene->addEllipse(corner_x+achsabstand-gearwheel2->getDiameter()/2*zoomfactor, corner_y-gearwheel2->getDiameter()/2*zoomfactor, gearwheel2->getDiameter()*zoomfactor, gearwheel2->getDiameter()*zoomfactor);
        }
    }

    if (visibility.diameter_foot) {
        // x, y, h, w
        scene->addEllipse(corner_x-gearwheel->getFootdiameter()/2*zoomfactor, corner_y-gearwheel->getFootdiameter()/2*zoomfactor, gearwheel->getFootdiameter()*zoomfactor, gearwheel->getFootdiameter()*zoomfactor);
        if (visibility.secondGearwheel) {
            scene->addEllipse(corner_x+achsabstand-gearwheel2->getFootdiameter()/2*zoomfactor, corner_y-gearwheel2->getFootdiameter()/2*zoomfactor, gearwheel2->getFootdiameter()*zoomfactor, gearwheel2->getFootdiameter()*zoomfactor);
        }
    }

    if (visibility.diameter_outer) {
        scene->addEllipse(corner_x-gearwheel->getOuterdiameter()/2*zoomfactor, corner_y-gearwheel->getOuterdiameter()/2*zoomfactor, gearwheel->getOuterdiameter()*zoomfactor, gearwheel->getOuterdiameter()*zoomfactor);
        if (visibility.secondGearwheel) {
            scene->addEllipse(corner_x+achsabstand-gearwheel2->getOuterdiameter()/2*zoomfactor, corner_y-gearwheel2->getOuterdiameter()/2*zoomfactor, gearwheel2->getOuterdiameter()*zoomfactor, gearwheel2->getOuterdiameter()*zoomfactor);
        }
    }

    if (visibility.diameter_base) {
        scene->addEllipse(corner_x-gearwheel->getBasediameter()/2*zoomfactor, corner_y-gearwheel->getBasediameter()/2*zoomfactor, gearwheel->getBasediameter()*zoomfactor, gearwheel->getBasediameter()*zoomfactor);
        if (visibility.secondGearwheel) {
            scene->addEllipse(corner_x+achsabstand-gearwheel2->getBasediameter()/2*zoomfactor, corner_y-gearwheel2->getBasediameter()/2*zoomfactor, gearwheel2->getBasediameter()*zoomfactor, gearwheel2->getBasediameter()*zoomfactor);
        }
    }

    delete gearwheelitem2;
    gearwheelitem2 = new GearwheelItem(*outputobj2, posx+achsabstand, posy, zoomfactor);
    if (visibility.secondGearwheel)
        scene->addItem(gearwheelitem2);
}

void GearwheelOutputController::rotate(float deg)
{
    mainlayout->changeStatusText("Rotiere...");
    gearwheel->rotate(deg);
    float seconddeg = -deg * gearwheel->getToothcount() / gearwheel2->getToothcount();
    if (visibility.secondGearwheel)
        gearwheel2->rotate(seconddeg);
    else
        rotationdiff += seconddeg;
    rotationpos += deg;
    repaintItem();
}

void GearwheelOutputController::rotate_fwd(void) { rotate(getRotationspeed()); }
void GearwheelOutputController::rotate_bwd(void) { rotate(-getRotationspeed()); }

void GearwheelOutputController::setConnections(void)
{
    connect(view, SIGNAL(changePosition(int,int)), this, SLOT(moveItem(int,int)));
    connect(view, SIGNAL(zoomIn()), this, SLOT(zoomItemIn()));
    connect(view, SIGNAL(zoomOut()), this, SLOT(zoomItemOut()));
    connect(view, SIGNAL(rotateFine()), this, SLOT(rotateSingle()));
    connect(view, SIGNAL(toggleRotation()), this, SLOT(toggleRotation()));
}

void GearwheelOutputController::createTimer(void)
{
    rotationtimer = new QTimer(this);
    connect(rotationtimer, SIGNAL(timeout()), this, SLOT(rotationTimerEvent()));
}

void GearwheelOutputController::createSecondGearwheel(void)
{
    Zahnraddaten tmp = gearwheel->getGearwheelData();
    Zahnraddaten dataGW2 = Zahnraddaten(tmp.alpha(), tmp.rho(), tmp.c(), tmp.m(), -tmp.x(), tmp.k(), tmp.z());
    gearwheel2 = new ProfilMathematisch(dataGW2, 50);
    outputobj2 = new GearwheelOutputQt(gearwheel2->zahnprofil);
    gearwheelitem2 = new GearwheelItem(*outputobj2, posx+(gearwheel->getDiameter() + gearwheel2->getDiameter())/2*zoomfactor, posy, zoomfactor);

    if (gearwheel->getToothcount() % 2 == gearwheel2->getToothcount() % 2)
        gearwheel2->rotate(360/gearwheel2->getToothcount());
}

void GearwheelOutputController::addSecondGearwheel(void)
{
    scene->addItem(gearwheelitem2);
    std::cout << scene->sceneRect().x() << " " << scene->sceneRect().y() << std::endl;
    std::cout << scene->sceneRect().width() << " " << scene->sceneRect().height() << std::endl;
}

void GearwheelOutputController::removeSecondGearwheel(void)
{
    scene->removeItem(gearwheelitem2);
}

void GearwheelOutputController::setToInitialPosition(void)
{
    gearwheel->rotateToFlankPoint();
    gearwheel2->rotateToFlankPoint();
}

void GearwheelOutputController::rotationTimerEvent(void)
{
    rotate_fwd();
}

void GearwheelOutputController::moveItem(int x, int y)
{
    posx = x;
    posy = y;
    repaintItem();
}

void GearwheelOutputController::zoomItemIn(void)
{
    zoomfactor *= 1.05;
    repaintItem();
}

void GearwheelOutputController::zoomItemOut(void)
{
    zoomfactor /= 1.05;
    repaintItem();
}

void GearwheelOutputController::rotateSingle(void)
{
    gearwheel->rotate(1);
    repaintItem();
}

void GearwheelOutputController::toggleSecondGearwheel(void)
{
    visibility.secondGearwheel = !visibility.secondGearwheel;
    if (visibility.secondGearwheel)
    {
        gearwheel2->rotate(rotationdiff);
        rotationdiff = 0;
        addSecondGearwheel();
        secondGearwheelVisChanged(true);
    }

    else {
        secondGearwheelVisChanged(false);
        removeSecondGearwheel();
    }
    repaintItem();
}

void GearwheelOutputController::centerGearwheel(void)
{
    posx = scene->sceneRect().width() / 2;
    posy = scene->sceneRect().height() / 2;
    repaintItem();
}

void GearwheelOutputController::changeSpeed(int newDeg)
{
    rot_vel = pow(10, (float)(1 + 2) / 99 * newDeg - 2);
    updateRotationspeed();
    //std::cout << newDeg << " " << rot_vel << std::endl;
}

void GearwheelOutputController::changeSteps(int x)
{
    float tempstepsize = pow(10, (float)-x * 3 / 100) * 500;
    stepsize = (int)tempstepsize;
    updateRotationspeed();
    rotationtimer->setInterval(stepsize);
    //std::cout << x << " " << stepsize << std::endl;
}

void GearwheelOutputController::updateRotationspeed(void)
{
    rotationdeg = rot_vel * DEG * stepsize;
}

float GearwheelOutputController::getRotationspeed(void)
{
    return rotationdeg;
}

void GearwheelOutputController::toggleRotation(void)
{
    if (rotationtimer->isActive()) {
        rotationtimer->stop();
        emit rotationStateChanged(false);
    }
    else {
        rotationtimer->start(stepsize);
        emit rotationStateChanged(true);
    }
}

void GearwheelOutputController::changeToothcount(int z)
{
    gearwheel->changeToothcount(z);
    fitGearwheels();
    repaintItem();
}

void GearwheelOutputController::changeToothcount2(int z)
{
    gearwheel2->changeToothcount(z);
    fitGearwheels();
    repaintItem();
}

void GearwheelOutputController::fitGearwheels(void)
{
    setToInitialPosition();
    if (gearwheel2->getToothcount() % 2 != 0)
    {
        gearwheel2->rotate(360/gearwheel2->getToothcount());
    }
    rotate(rotationpos);
    rotationpos /= 2;
}

void GearwheelOutputController::changeX(double x)
{
    gearwheel->changeX(x);
    gearwheel2->changeX(-x);
    fitGearwheels();
    repaintItem();
}

void GearwheelOutputController::setDiameterVisibility(int state)
{
    visibility.diameter = (bool)state;
    repaintItem();
}

void GearwheelOutputController::setFootdiameterVisibility(int state)
{
    visibility.diameter_foot = (bool)state;
    repaintItem();
}

void GearwheelOutputController::setOuterdiameterVisibility(int state)
{
    visibility.diameter_outer = (bool)state;
    repaintItem();
}

void GearwheelOutputController::setBasediameterVisibility(int state)
{
    visibility.diameter_base = (bool)state;
    repaintItem();
}

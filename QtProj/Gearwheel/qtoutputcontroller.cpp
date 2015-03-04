#include "qtoutputcontroller.h"

GearwheelOutputController::GearwheelOutputController(QObject *parent, GearwheelOutputView* view, ProfilMathematisch* zahnrad)
    : QObject(parent), view(view), gearwheel(zahnrad)
{
    posx = 250;
    posy = 250;
    zoomfactor = 5;
    rotationdeg = .5;
    stepsize = 100;
    rotationdiff = 0;
    rotationpos = 0;

    secondGearwheelVisible = false;
    diameterVisible = true;

    rotating = false;
    scene = new QGraphicsScene(view);
    outputobj = new GearwheelOutputQt(gearwheel->zahnprofil);
    gearwheelitem = new GearwheelItem(*outputobj, posx, posy, zoomfactor);
    view->setScene(scene);
    scene->addItem(gearwheelitem);
    view->adjustSize();

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
    if (secondGearwheelVisible)
        scene->removeItem(gearwheelitem2);
    scene->clear();
    delete gearwheelitem;
    gearwheelitem = new GearwheelItem(*outputobj, posx, posy, zoomfactor);
    scene->addItem(gearwheelitem);

    if (diameterVisible) {
        scene->addEllipse(-600+posx-gearwheel->getDiameter()/2*zoomfactor, -600+posy-gearwheel->getDiameter()/2*zoomfactor, gearwheel->getDiameter()*zoomfactor, gearwheel->getDiameter()*zoomfactor);
        if (secondGearwheelVisible) {
            scene->addEllipse(-600+posx+(gearwheel->getDiameter() + gearwheel2->getDiameter())/2*zoomfactor-gearwheel2->getDiameter()/2*zoomfactor, -600+posy-gearwheel2->getDiameter()/2*zoomfactor, gearwheel2->getDiameter()*zoomfactor, gearwheel2->getDiameter()*zoomfactor);
        }
    }

    delete gearwheelitem2;
    gearwheelitem2 = new GearwheelItem(*outputobj2, posx+(gearwheel->getDiameter() + gearwheel2->getDiameter())/2*zoomfactor, posy, zoomfactor);
    if (secondGearwheelVisible)
        scene->addItem(gearwheelitem2);
}

void GearwheelOutputController::rotate(float deg)
{
    gearwheel->rotate(deg);
    float seconddeg = -deg * gearwheel->getToothcount() / gearwheel2->getToothcount();
    if (secondGearwheelVisible)
        gearwheel2->rotate(seconddeg);
    else
        rotationdiff += seconddeg;
    rotationpos += deg;
    repaintItem();
}

void GearwheelOutputController::rotate_fwd(void) { rotate(rotationdeg); }
void GearwheelOutputController::rotate_bwd(void) { rotate(-rotationdeg); }

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
    Zahnraddaten dataGW2 = Zahnraddaten(tmp.alpha, tmp.rho, tmp.c, tmp.m, -tmp.x, tmp.k, tmp.z);
    gearwheel2 = new ProfilMathematisch(dataGW2, 50);
    outputobj2 = new GearwheelOutputQt(gearwheel2->zahnprofil);
    gearwheelitem2 = new GearwheelItem(*outputobj2, posx+(gearwheel->getDiameter() + gearwheel2->getDiameter())/2*zoomfactor, posy, zoomfactor);

    if (gearwheel->getToothcount() % 2 == gearwheel2->getToothcount() % 2)
        gearwheel2->rotate(360/gearwheel2->getToothcount());
}

void GearwheelOutputController::addSecondGearwheel(void)
{
    scene->addItem(gearwheelitem2);
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
    secondGearwheelVisible = !secondGearwheelVisible;
    if (secondGearwheelVisible)
    {
        gearwheel2->rotate(rotationdiff);
        rotationdiff = 0;
        addSecondGearwheel();
    }

    else removeSecondGearwheel();
}

void GearwheelOutputController::changeSpeed(int newDeg)
{
    rotationdeg = (float)newDeg/10;
}

void GearwheelOutputController::changeSteps(int x)
{
    std::cout << x << std::endl;
    stepsize = (x+1)*10;
    rotationtimer->setInterval(stepsize);
}

void GearwheelOutputController::toggleRotation(void)
{
    if (rotationtimer->isActive()) rotationtimer->stop();
    else rotationtimer->start(stepsize);
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
    // TODO: Nicht zurücksetzen, stattdessen auf aktuellen Rotationswinkel beziehen
    setToInitialPosition();
    if (gearwheel2->getToothcount() % 2 != 0)
    {
        std::cout << "Rotate2" << std::endl;
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

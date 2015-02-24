#include "qtoutputcontroller.h"

GearwheelOutputController::GearwheelOutputController(QObject *parent, GearwheelOutputView* view, ProfilMathematisch* zahnrad)
    : QObject(parent), view(view), gearwheel(zahnrad)
{
    posx = 250;
    posy = 250;
    zoomfactor = 5;

    secondGearwheelVisible = false;

    rotating = false;
    scene = new QGraphicsScene(view); //GearwheelOutputScene(view);
    outputobj = new GearwheelOutputQt(gearwheel->zahnprofil);
    gearwheelitem = new GearwheelItem(*outputobj, posx, posy, zoomfactor);
    view->setScene(scene);
    scene->addItem(gearwheelitem);
    view->adjustSize();

    createSecondGearwheel();
    if (gearwheel->zahnrad.z % 2 == gearwheel2->zahnrad.z % 2)
    {
        gearwheel2->rotateGearwheel(360/gearwheel2->zahnrad.z);
        std::cout << "Zusatz" << std::endl;
    }

    setConnections();
}

GearwheelOutputController::~GearwheelOutputController(void) {
    delete scene;
    delete outputobj;
    delete outputobj2;
    delete gearwheel2;
    delete gearwheelitem;
    delete gearwheelitem2;
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
    //scene->addEllipse(-600+posx+(gearwheel->zahnrad.durchmesser.d + gearwheel2->zahnrad.durchmesser.d)/2*zoomfactor-gearwheel2->zahnrad.durchmesser.d/2*zoomfactor, -600+posy-gearwheel2->zahnrad.durchmesser.d/2*zoomfactor, gearwheel2->zahnrad.durchmesser.d*zoomfactor, gearwheel2->zahnrad.durchmesser.d*zoomfactor);
    //scene->addEllipse(-600+posx-gearwheel->zahnrad.durchmesser.d/2*zoomfactor, -600+posy-gearwheel->zahnrad.durchmesser.d/2*zoomfactor, gearwheel->zahnrad.durchmesser.d*zoomfactor, gearwheel->zahnrad.durchmesser.d*zoomfactor);

    delete gearwheelitem2;
    gearwheelitem2 = new GearwheelItem(*outputobj2, posx+(gearwheel->zahnrad.durchmesser.d + gearwheel2->zahnrad.durchmesser.d)/2*zoomfactor, posy, zoomfactor);
    if (secondGearwheelVisible)
        scene->addItem(gearwheelitem2);
}

void GearwheelOutputController::rotate(float deg)
{
    gearwheel->rotateGearwheel(deg);
    gearwheel2->rotateGearwheel(-deg * gearwheel->zahnrad.z / gearwheel2->zahnrad.z);
    repaintItem();
}

void GearwheelOutputController::rotate_fwd(void) { rotate(.5);  }
void GearwheelOutputController::rotate_bwd(void) { rotate(-.5); }
void GearwheelOutputController::toggleRotation(void) { rotating = !rotating; }

void GearwheelOutputController::setConnections(void)
{
    connect(view, SIGNAL(changePosition(int,int)), this, SLOT(moveItem(int,int)));
    connect(view, SIGNAL(zoomIn()), this, SLOT(zoomItemIn()));
    connect(view, SIGNAL(zoomOut()), this, SLOT(zoomItemOut()));
    connect(view, SIGNAL(rotateFine()), this, SLOT(rotateSingle()));
    connect(view, SIGNAL(rotateFull()), this, SLOT(rotate_fwd()));
}

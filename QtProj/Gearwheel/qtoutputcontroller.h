#ifndef QTOUTPUTCONTROLLER_H
#define QTOUTPUTCONTROLLER_H

#include "zahnradmath.h"
#include "qtoutputscene.h"
#include "gearwheeloutput.h"
#include <QGraphicsItem>
#include <QObject>

#include <iostream>

class GearwheelOutputScene : public QGraphicsScene
{
public:
    GearwheelOutputScene(QObject *parent)
        : QGraphicsScene(parent) { }
};

class GearwheelItem : public QGraphicsItem
{
private:
    GearwheelOutputQt& outputobj;
    int radius;
    float zoom;
    float angle;
    int pos_x;
    int pos_y;

public:
    GearwheelItem(GearwheelOutputQt& outputobject)
        : outputobj(outputobject), radius(600), zoom(5), angle(0), pos_x(200), pos_y(200) { }
    GearwheelItem(GearwheelOutputQt& outputobject, int x, int y, float zoomfactor)
        : outputobj(outputobject), radius(600), zoom(zoomfactor), angle(0.0), pos_x(x), pos_y(y) { }
    GearwheelItem(GearwheelOutputQt& outputobject, int x, int y, float zoomfactor, float angle)
        : outputobj(outputobject), radius(600), zoom(zoomfactor), angle(angle), pos_x(x), pos_y(y) { }

    QRectF boundingRect() const
    {
        return QRectF(-radius, -radius, radius, radius);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        if (angle == 0)
            outputobj.printToDisplay(*painter, -radius+pos_x,-radius+pos_y,zoom);
        else
            outputobj.printToDisplay(*painter, -radius+pos_x, -radius+pos_y,zoom,angle);
        painter->drawLine(-5-radius+pos_x,-5-radius+pos_y,5-radius+pos_x,5-radius+pos_y);
        painter->drawLine(5-radius+pos_x,-5-radius+pos_y,-5-radius+pos_x,5-radius+pos_y);
    }
};

class GearwheelOutputController : public QObject
{
    Q_OBJECT

private:
    //GearwheelOutputScene* scene;
    QGraphicsScene *scene;
    GearwheelOutputView* view;
    ProfilMathematisch* gearwheel; // Modell
    ProfilMathematisch* gearwheel2;
    GearwheelOutputQt* outputobj;
    GearwheelOutputQt* outputobj2;
    GearwheelItem* gearwheelitem;
    GearwheelItem* gearwheelitem2;

    bool rotating;
    bool secondGearwheelVisible;

    int posx;
    int posy;
    float zoomfactor;

    void createSecondGearwheel(void)
    {
        Zahnraddaten tmp = gearwheel->zahnrad;
        Zahnraddaten dataGW2 = Zahnraddaten(tmp.alpha, tmp.rho, tmp.c, tmp.m, tmp.x, tmp.k, tmp.z * 0.8);
        gearwheel2 = new ProfilMathematisch(dataGW2, 50);
        outputobj2 = new GearwheelOutputQt(gearwheel2->zahnprofil);
        gearwheelitem2 = new GearwheelItem(*outputobj2, posx+(gearwheel->zahnrad.durchmesser.d + gearwheel2->zahnrad.durchmesser.d)/2*zoomfactor, posy, zoomfactor);
    }

    void addSecondGearwheel(void)
    {
        scene->addItem(gearwheelitem2);
    }

    void removeSecondGearwheel(void)
    {
        scene->removeItem(gearwheelitem2);
    }

public:
   /* GearwheelOutputController(QObject* parent)
        : QObject(parent) { }*/

    GearwheelOutputController(QObject *parent, GearwheelOutputView* view, ProfilMathematisch* zahnrad)
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
    }

    ~GearwheelOutputController(void) {
        delete scene;
        delete outputobj;
        delete outputobj2;
        delete gearwheel2;
        delete gearwheelitem;
        delete gearwheelitem2;
    }

    void repaintItem(void)
    {
        scene->removeItem(gearwheelitem);
        delete gearwheelitem;
        gearwheelitem = new GearwheelItem(*outputobj, posx, posy, zoomfactor);
        scene->addItem(gearwheelitem);

        if (secondGearwheelVisible)
            scene->removeItem(gearwheelitem2);
        delete gearwheelitem2;
        gearwheelitem2 = new GearwheelItem(*outputobj2, posx+(gearwheel->zahnrad.durchmesser.d + gearwheel2->zahnrad.durchmesser.d)/2*zoomfactor, posy, zoomfactor);
        if (secondGearwheelVisible)
            scene->addItem(gearwheelitem2);
    }

    void rotate(float deg)
    {
        gearwheel->rotateGearwheel(deg);
        gearwheel2->rotateGearwheel(-deg * gearwheel->zahnrad.z / gearwheel2->zahnrad.z);
        repaintItem();
    }

    void rotate_fwd(void) { rotate(.5);  }
    void rotate_bwd(void) { rotate(-.5); }

    void toggleRotation(void) {
        rotating = !rotating;
    }


public slots:
    void updateData()
    {
        std::cout << "Daten updaten" << std::endl;
    }

    void moveItem(int x, int y)
    {
        posx = x;
        posy = y;
        repaintItem();
    }

    void zoomItemIn(void)
    {
        zoomfactor *= 1.05;
        repaintItem();
    }

    void zoomItemOut(void)
    {
        zoomfactor /= 1.05;
        repaintItem();
    }

    void rotateSingle()
    {
        gearwheel->rotateGearwheel(1);
        repaintItem();
    }

    void toggleSecondGearwheel(void)
    {
        secondGearwheelVisible = !secondGearwheelVisible;
        if (secondGearwheelVisible) addSecondGearwheel();
        else removeSecondGearwheel();
    }

};

#endif // QTOUTPUTCONTROLLER_H

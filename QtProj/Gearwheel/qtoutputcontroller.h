#ifndef QTOUTPUTCONTROLLER_H
#define QTOUTPUTCONTROLLER_H

#include "zahnradmath.h"
#include "qtoutputscene.h"
#include "gearwheeloutput.h"
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

#include <iostream>

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
    QGraphicsScene *scene;
    GearwheelOutputView* view;

    ProfilMathematisch* gearwheel; // Modell
    ProfilMathematisch* gearwheel2;
    GearwheelOutputQt* outputobj;
    GearwheelOutputQt* outputobj2;
    GearwheelItem* gearwheelitem;
    GearwheelItem* gearwheelitem2;
    QTimer* rotationtimer;

    bool rotating;
    bool secondGearwheelVisible;

    int posx;
    int posy;
    float zoomfactor;
    float rotationdeg;

    int stepsize;

    void createTimer(void);
    void createSecondGearwheel(void);

    void addSecondGearwheel(void);
    void removeSecondGearwheel(void);

    void setConnections(void);

public:
    GearwheelOutputController(QObject *parent, GearwheelOutputView* view, ProfilMathematisch* zahnrad);
    ~GearwheelOutputController(void);

    void repaintItem(void);
    void rotate(float deg);
    void rotate_bwd(void);

public slots:
    void rotationTimerEvent(void)
    {
        rotate_fwd();
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

    void changeSpeed(int newDeg)
    {
        rotationdeg = (float)newDeg/10;
    }

    void rotate_fwd(void);

    void changeSteps(int x)
    {
        std::cout << x << std::endl;
        stepsize = (x+1)*10;
        rotationtimer->setInterval(stepsize);
    }

    void toggleRotation()
    {
        if (rotationtimer->isActive()) rotationtimer->stop();
        else rotationtimer->start(stepsize);
    }

};

#endif // QTOUTPUTCONTROLLER_H

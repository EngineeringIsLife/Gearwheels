#ifndef QTOUTPUTCONTROLLER_H
#define QTOUTPUTCONTROLLER_H

#include "zahnradmath.h"
#include "qtoutputview.h"
#include "gearwheeloutput.h"
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

#include <iostream>

#include "mainlayout.h"

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
    MainLayout* mainlayout;

    ProfilMathematisch* gearwheel; // Modell
    ProfilMathematisch* gearwheel2;
    GearwheelOutputQt* outputobj;
    GearwheelOutputQt* outputobj2;
    GearwheelItem* gearwheelitem;
    GearwheelItem* gearwheelitem2;
    QTimer* rotationtimer;

    bool rotating;

    struct
    {
        bool secondGearwheel;
        bool diameter;
        bool diameter_foot;
        bool diameter_outer;
        bool diameter_base;
    } visibility;

    int posx;
    int posy;
    float zoomfactor;
    float rotationdeg;
    float rotationpos;
    float rotationdiff;

    int stepsize;

    float rot_vel;

    void createTimer(void);
    void createSecondGearwheel(void);

    void addSecondGearwheel(void);
    void removeSecondGearwheel(void);

    void setConnections(void);

    float getRotationspeed(void);
    void updateRotationspeed(void);

    void zoomCentered(float factor, int centerx, int centery);

public:
    GearwheelOutputController(QObject *parent, GearwheelOutputView* view, MainLayout* mainlayout, ProfilMathematisch* zahnrad);
    ~GearwheelOutputController(void);

    void repaintItem(void);
    void rotate(float deg);
    void rotate_bwd(void);

    void setToInitialPosition(void);
    void fitGearwheels(void);

public slots:
    void rotationTimerEvent(void);
    void moveItem(int x, int y);
    void zoomItemIn(int x, int y);
    void zoomItemOut(int x, int y);
    void rotateSingle(void);
    void toggleSecondGearwheel(void);
    void centerGearwheel(void);
    void changeSpeed(int newDeg);
    void rotate_fwd(void);
    void changeSteps(int x);
    void toggleRotation(void);
    void changeToothcount(int z);
    void changeToothcount2(int z);
    void changeX(double x);
    void setDiameterVisibility(int state);
    void setFootdiameterVisibility(int state);
    void setOuterdiameterVisibility(int state);
    void setBasediameterVisibility(int state);
    void setModul(QString modul);
    void setModul(float modul);

signals:
    void rotationStateChanged(bool state);
    void secondGearwheelVisChanged(bool state);
};

#endif // QTOUTPUTCONTROLLER_H

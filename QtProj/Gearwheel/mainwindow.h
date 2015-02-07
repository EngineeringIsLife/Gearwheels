#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>

#include "gearwheeloutput.h"
//#include <QPainter>
//#include <QMainWindow>

class GearwheelItem : public QGraphicsItem
{
private:
    GearwheelOutputQt& outputobj;
    int radius;
    float zoom;
    int pos_x, pos_y;
public:
    GearwheelItem(GearwheelOutputQt& outputobject, int x, int y, float zoomfactor)
        : pos_x(x), pos_y(y), outputobj(outputobject), zoom(zoomfactor) { radius = 500; }

    QRectF boundingRect() const
    {
        return QRectF(-radius, -radius, radius, radius);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        outputobj.printToDisplay(*painter, -pos_x,-pos_y,zoom);
        painter->drawLine(-5,-5,5,5);
        painter->drawLine(5,-5,-5,5);

    }
};

class GraphicView : public QGraphicsView
{
public:
    int posx, posy;

    explicit GraphicView(QWidget *parent = 0)
        : QGraphicsView(parent) { }
    virtual void mouseMoveEvent(QMouseEvent *ev);
};

//class MainWindow : public QMainWindow
class MainWidget : public QWidget
{
    Q_OBJECT

private:
    //Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    GearwheelItem *gearwheelitem;
    GraphicView *outputZone;

    bool rotationStarted;
    float zoom;
    float angle;

    void updateGearwheel(void);

    //virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);  // Replace with wheelEvent

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void rotationTimer(void);
    void toggleRotation(void);
};

#endif // MAINWINDOW_H

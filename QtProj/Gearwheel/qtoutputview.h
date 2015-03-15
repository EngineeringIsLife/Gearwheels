#ifndef QTOUTPUTSCENE_H
#define QTOUTPUTSCENE_H

#include "zahnradmath.h"
#include <iostream>
#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QTimer>

// View
class GearwheelOutputView : public QGraphicsView
{
    Q_OBJECT

private:
    QWidget* parent;

    int posx, posy;
    int startx, starty;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

public:
    explicit GearwheelOutputView(QWidget *parent); //, ProfilMathematisch* zahnrad);
    ~GearwheelOutputView(void);
    void setPos(int x, int y);

signals:
    void changePosition(int x, int y);
    void zoomIn(int x, int y);
    void zoomOut(int x, int y);
    void toggleRotation();
    void rotateFine();

public slots:
    void passPlus(void);
    void passMinus(void);
};

#endif // QTOUTPUTSCENE_H

#include "qtoutputscene.h"
#include <QGraphicsView>
#include <iostream>

#include <QPushButton>
#include <QWheelEvent>

GearwheelOutputView::GearwheelOutputView(QWidget *parent)
    : QGraphicsView(parent), parent(parent)
{
    posx = 200;
    posy = 200;
    QPushButton *button_plus = new QPushButton("+", parent=this);
    QPushButton *button_minus = new QPushButton("-", parent=this);

    button_plus->setGeometry(10,10,20,25);
    button_minus->setGeometry(10,30,20,25);

    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setDragMode(NoDrag);
    //setSceneRect(-0.5,-0.5,1,1);

    connect(button_plus, SIGNAL(clicked()), this, SLOT(passPlus()));
    connect(button_minus, SIGNAL(clicked()), this, SLOT(passMinus()));
}

GearwheelOutputView::~GearwheelOutputView(void)
{ }

void GearwheelOutputView::setPos(int x, int y)
{
    posx = x;
    posy = y;
}

void GearwheelOutputView::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        startx = event->pos().x() - posx;
        starty = event->pos().y() - posy;
    }
}

void GearwheelOutputView::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)// && ev->modifiers().testFlag(Qt::ControlModifier))
    {
        QPointF pos = ev->pos();
        posx = -startx + pos.x();
        posy = -starty + pos.y();
        emit changePosition(posx, posy);
    }
}

void GearwheelOutputView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Plus:
        emit zoomIn();
        break;
    case Qt::Key_Minus:
        emit zoomOut();
        break;
    case Qt::Key_F:
        emit rotateFine();
        break;
    case Qt::Key_R:
        emit toggleRotation();
        break;
    case Qt::Key_Up:
        posy += 10;
        emit changePosition(posx, posy);
        break;
    case Qt::Key_Down:
        posy -= 10;
        emit changePosition(posx, posy);
        break;
    case Qt::Key_Left:
        posx += 10;
        emit changePosition(posx, posy);
        break;
    case Qt::Key_Right:
        posx -= 10;
        emit changePosition(posx, posy);
        break;
    }
}

void GearwheelOutputView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() >= 0)
        zoomIn();
    else
        zoomOut();
}

void GearwheelOutputView::passPlus(void)
{
    emit zoomIn();
}

void GearwheelOutputView::passMinus(void)
{
    emit zoomOut();
}

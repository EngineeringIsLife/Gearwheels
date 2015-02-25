#include "qtoutputscene.h"
#include <QGraphicsView>
#include <iostream>


GearwheelOutputView::GearwheelOutputView(QWidget *parent)
    : QGraphicsView(parent), parent(parent)
{ posx = 200; posy = 200; }

GearwheelOutputView::~GearwheelOutputView(void)
{ }

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

#include "qtoutputscene.h"
#include <QGraphicsView>
#include <iostream>

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

        //update();
        emit changePosition(posx, posy); //changedView();
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
    }
}

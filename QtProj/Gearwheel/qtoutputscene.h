#ifndef QTOUTPUTSCENE_H
#define QTOUTPUTSCENE_H

#include "zahnradmath.h"

//#include "gearwheeloutput.h"
#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>

// View
class GearwheelOutputView : public QGraphicsView
{
    Q_OBJECT

private:
    QWidget* parent;
    ProfilMathematisch* gearwheel;

    int posx, posy;
    int startx, starty;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void keyPressEvent(QKeyEvent *event);

public:

    explicit GearwheelOutputView(QWidget *parent = 0)
        : QGraphicsView(parent), parent(parent), gearwheel(0) { posx = 200; posy = 200; }

    explicit GearwheelOutputView(QWidget *parent, ProfilMathematisch* zahnrad)
        : QGraphicsView(parent), parent(parent), gearwheel(zahnrad)
    { posx = 200; posy = 200; }

    ~GearwheelOutputView(void)
    {   }

public: // signals
signals:
    void changePosition(int x, int y);
    void changedView();
    void zoomIn();
    void zoomOut();
    void rotateFine();
};

#endif // QTOUTPUTSCENE_H

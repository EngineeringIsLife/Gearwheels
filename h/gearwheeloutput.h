#ifndef GEARWHEELOUTPUT_H
#define GEARWHEELOUTPUT_H

#include "zahnradprofil.h"
#include <iostream>
#include <QPainter>
#include <QGraphicsScene>

class GearwheelOutput
{
protected:
    Profile& profil;

public:
    GearwheelOutput(Profile& profile);

    void printProfile(std::ostream &stream);
    void printProfileToMatlab(std::ostream &stream);
};


class GearwheelOutputQt : public GearwheelOutput
{
public:
    GearwheelOutputQt(Profile& profile) : GearwheelOutput(profile) { }
    void printToDisplay(QPainter& painter, int center_x, int center_y, float scale);
    void printToDisplay(QPainter& painter, int center_x, int center_y, float scale, float rotation);
    void printToDisplay(QGraphicsScene& scene, int center_x, int center_y, float scale);
};

#endif // GEARWHEELOUTPUT_H

#include <iostream>
#include <qpainter.h>
#include <QGraphicsScene>

#include "zahnradfertigung.h"
#include "zahnradmath.h"
#include "gearwheeloutput.h"

GearwheelOutput::GearwheelOutput(Profile& profile)
    : profil(profile)
{
    std::cout << "Output Konstruktor" << std::endl;
}

void GearwheelOutput::printProfileToMatlab(std::ostream &stream)
{
    stream << "zahnrad = [" << std::endl;
    profil.resetIterator();

    stream << profil.getNextX() << ", " << profil.getNextY();
    while (!profil.iteratorEndReached())
    {
        stream << ";" << std::endl << profil.getNextX() << ", " << profil.getNextY();
    }
    stream << "]" << std::endl;
}

void GearwheelOutput::printProfile(std::ostream &stream)
{
    profil.resetIterator();
    while (!profil.iteratorEndReached())
    {
        stream << profil.getNextX() << " " << profil.getNextY() << std::endl;
    }
    profil.resetIterator();
}

// ------------

void GearwheelOutputQt::printToDisplay(QPainter& painter, int center_x, int center_y, float scale)
{
    profil.resetIterator();
    int p1 = (int)(profil.getNextX() * scale) + center_x;
    int p2 = (int)(profil.getNextY() * scale) + center_y;

    while(!profil.iteratorEndReached())
    {
        int p3 = (int)(profil.getNextX() * scale) + center_x;
        int p4 = (int)(profil.getNextY() * scale) + center_y;
        painter.drawLine(p1, p2, p3, p4);
        p1 = p3;
        p2 = p4;
    }
}

void GearwheelOutputQt::printToDisplay(QGraphicsScene& scene, int center_x, int center_y, float scale)
{
    profil.resetIterator();
    int p1 = (int)(profil.getNextX() * scale) + center_x;
    int p2 = (int)(profil.getNextY() * scale) + center_y;

    while(!profil.iteratorEndReached())
    {
        int p3 = (int)(profil.getNextX() * scale) + center_x;
        int p4 = (int)(profil.getNextY() * scale) + center_y;
        scene.addLine(p1, p2, p3, p4, QPen(Qt::black));
        p1 = p3;
        p2 = p4;
    }
}

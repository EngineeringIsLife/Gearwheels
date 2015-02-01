#include <iostream>

#include "bezugsprofil.h"
#include "zahnradmath.h"
#include "gearwheeloutput.h"

GearwheelOutput::GearwheelOutput(Profil& profile)
    : profil(profile)
{
    //std::cout << "Output Konstruktor" << std::endl;
}

/*
void GearwheelOutput::printProfile(std::ostream &stream)
{
    // TODO: Auf komplettes Profil anpassen (2 entfernen)
    for (int i = 0; i < zahnrad.parts_per_tooth; i++)
    {
        stream << zahnprofil.getX(i) << " " << zahnprofil.getY(i) << std::endl;
    }
}

void GearwheelOutput::printProfileToMatlab(std::ostream &stream)
{
    stream << "profil = [" << std::endl;
    for (int i = 0; i < parts_per_tooth*zahnrad.z - 1; i++)
         stream << zahnprofil.getX(i) << ", " << zahnprofil.getY(i) << ";" << std::endl;
    stream << zahnprofil.getX(parts_per_tooth - 1) << ", " << zahnprofil.getY(parts_per_tooth - 1) << "];";
}
*/

void GearwheelOutput::printProfile(std::ostream &stream)
{
    profil.resetIterator();
    while (!profil.iteratorEndReached())
    {
        stream << profil.getNextX() << " " << profil.getNextY() << std::endl;
    }
    profil.resetIterator();
}

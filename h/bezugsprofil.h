#ifndef BEZUGSPROFIL_H
#define BEZUGSPROFIL_H

#include "zahnradprofil.h"
#include "zahnrad.h"

#define DEG (M_PI/180.0)

class Bezugsprofil
{
private:
    Zahnraddaten zahnrad;
    float schrittweite; // Rechenschrittweite - evtl in anderer funktion besser aufgehoben

    void calcBezugsprofil(void);

public:
    Profile profil;

    Bezugsprofil(Zahnraddaten zahnrad, float schrittweite, float genauigkeit);
    Bezugsprofil(float alpha, float rho, float c, float schrittweite, float genauigkeit, float m, float x, float k, int z);
    ~Bezugsprofil(void);

    void printProfile(std::ostream &stream);            // Todo: in eigene Klasse (Model View Control!)
    void printProfileToMatlab(std::ostream &stream);
};

#endif // BEZUGSPROFIL_H

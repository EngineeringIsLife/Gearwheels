#ifndef BEZUGSPROFIL_H
#define BEZUGSPROFIL_H

#include "zahnrad.h"

#define DEG (M_PI/180.0)

class Bezugsprofil
{
private:
    Zahnraddaten zahnrad;

    float schrittweite; // Rechenschrittweite - evtl in anderer funktion besser aufgehoben
    int genauigkeit;    // siehe Rechenschrittweite

    float *profil;
    float *profilx;

public:
    Bezugsprofil(float alpha, float rho, float c, float schrittweite, float genauigkeit, float m, float x, float k, int z)
        : zahnrad(alpha, rho, c, m, x, k, z), schrittweite(schrittweite), genauigkeit(genauigkeit) { }
    Bezugsprofil(Zahnraddaten zahnrad, float schrittweite, float genauigkeit)
        : zahnrad(zahnrad), schrittweite(schrittweite), genauigkeit(genauigkeit) { }
    ~Bezugsprofil(void);
    void calcBezugsprofil(void);
    void printProfile(std::ostream &stream);            // Todo: in eigene Klasse (Model View Control!)
    void printProfileToMatlab(std::ostream &stream);
};

#endif // BEZUGSPROFIL_H

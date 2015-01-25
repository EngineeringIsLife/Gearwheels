#ifndef BEZUGSPROFIL_H
#define BEZUGSPROFIL_H

#include "zahnrad.h"

class Bezugsprofil
{
private:
    Zahnrad zahnrad;

    float schrittweite; // Rechenschrittweite - evtl in anderer funktion besser aufgehoben
    int genauigkeit;    // siehe Rechenschrittweite

    float *profil;
    float *profilx;

public:
    Bezugsprofil(float alpha, float rho, float c, float schrittweite, float genauigkeit, float m, float x, float k, int z)
        : zahnrad(alpha, rho, c, m, x, k, z), schrittweite(schrittweite), genauigkeit(genauigkeit) { }
    Bezugsprofil(Zahnrad zahnrad, float schrittweite, float genauigkeit)
        : zahnrad(zahnrad), schrittweite(schrittweite), genauigkeit(genauigkeit) { }
    ~Bezugsprofil(void);
    void calcBezugsprofil(void);
    void printProfile(std::ostream &stream);            // Todo: in eigene Klasse (Model View Control!)
    void printProfileToMatlab(std::ostream &stream);
};


class Zahnradprofil
{
private:
    float* winkel;
    float* laenge;

public:
    Zahnradprofil(int elemente);
    ~Zahnradprofil(void);

    int elemente;

    void setAngle(int pos_id, float angle);
    void setLength(int pos_id, float angle);
    void setX(int pos_id, float x);
    void setY(int pos_id, float y);

    float getAngle(int pos_id);
    float getLength(int pos_id);
    float getX(int pos_id);
    float getY(int pos_id);
};


class ProfilMathematisch
{
private:
    Zahnrad zahnrad;
    Zahnradprofil zahnprofil;

    int genauigkeit;
    int parts_per_tooth;
    int parts_per_flank;

    float phi_min;
    float phi_max;

    float limits[4];

    void calcProfile(void);
    void calcLimits(void);
    void calcLeftFlank(void);
    void calcHead(void);
    void calcRightFlank(void);
    void calcFullXY(void);
    void calcFoot(void);

public:
    ProfilMathematisch(Zahnrad zahnrad, int genauigkeit);
    void printProfile(std::ostream &stream);
    void printProfileToMatlab(std::ostream &stream);
};

#endif // BEZUGSPROFIL_H

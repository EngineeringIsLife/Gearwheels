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


class Zahnradprofil
{
private:
    float* winkel;
    float* laenge;

    int iteratX, iteratY;

public:
    Zahnradprofil(int elemente);
    Zahnradprofil(Zahnradprofil& rhs);
    ~Zahnradprofil(void);

    int elemente;

    void setCartesian(int pos_id, float x, float y);
    void setPolar(int pos_id, float length, float angle);

    //void setAngle(int pos_id, float angle);
    //void setLength(int pos_id, float angle);
    void setX(int pos_id, float x);
    void setY(int pos_id, float y);

    float getAngle(int pos_id);
    float getLength(int pos_id);
    float getX(int pos_id);
    float getY(int pos_id);

    void resetIterator(void);
    bool iteratorEndReached(void);
    float getNextX(void);
    float getNextY(void);
};




#endif // BEZUGSPROFIL_H

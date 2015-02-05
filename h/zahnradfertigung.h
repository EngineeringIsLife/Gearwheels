#ifndef ZAHNRADFERTIGUNG_H
#define ZAHNRADFERTIGUNG_H

#include "zahnradprofil.h"
#include "zahnrad.h"

#define DEG (M_PI/180.0)

class Zahnrad
{
protected:
    Zahnraddaten zahnrad;
    int genauigkeit;

    virtual void calcProfile(void) = 0;

public:
    Profile zahnprofil;
    Zahnrad(Zahnraddaten zahnrad, int genauigkeit);

    void rotate(float deg);
    void move(float x, float y);

    void resetIterator(void);
    bool iteratorEndReached(void);
    float getNextX(void);
    float getNextY(void);
};

class ZahnradFertigung : public Zahnrad
{
private:
    //Zahnraddaten zahnrad;
    float schrittweite; // Rechenschrittweite - evtl in anderer funktion besser aufgehoben

    void calcProfile(void);

public:
    //Profile zahnprofil;

    ZahnradFertigung(Zahnraddaten zahnrad, float schrittweite, int genauigkeit);
    //ZahnradFertigung(float alpha, float rho, float c, float schrittweite, intt genauigkeit, float m, float x, float k, int z);
};

#endif

#ifndef ZAHNRAD_H
#define ZAHNRAD_H

#include "zahnradprofil.h"

#define DEG (M_PI/180.0)

class Zahnraddaten
{
private:
    const int itersteps;
    void calcDurchmesser(void);

public:
    float alpha;        // Profilwinkel
    float rho;          // Fussrundungsradius
    float c;            // Kopfspiel-Faktor

    float m;            // Modul
    float x;            // Profilverschiebungsfaktor
    float k;            // Kopfkuerzungsfaktor

    int z;              // Zaehnezahl

    struct
    {
        float d;    // Waelzkreisdurchmesser
        float d_a;  // Aussendurchmesser
        float d_b;  // Basiskreisdurchmesser
        float d_f;  // Fusskreisdurchmesser

        float d_max; // Maximaler Aussendurchmesser
    } durchmesser;

    Zahnraddaten(float alpha, float rho, float c, float m, float x, float k, int z);

};

class Zahnrad
{
protected:
    Zahnraddaten zahnrad;
    int profilepoints;

    virtual void calcProfile(void) = 0;

public:
    Profile zahnprofil;
    Zahnrad(Zahnraddaten zahnrad, int profilepoints);

    void rotate(float deg);
    void move(float x, float y);

    void resetIterator(void);
    bool iteratorEndReached(void);
    float getNextX(void);
    float getNextY(void);

    float getDiameter(void);
    int getToothcount(void);
    Zahnraddaten getGearwheelData(void);
};

#endif // ZAHNRAD_H

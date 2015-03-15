#ifndef ZAHNRAD_H
#define ZAHNRAD_H

#include "zahnradprofil.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#define M_PI_2 1.5707963267948966192313216916398
#endif

#define DEG (M_PI/180.0)

class Zahnraddaten
{
private:
    const int itersteps;
    void calcDurchmesser(void);

    float _alpha;        // Profilwinkel
    float _rho;          // Fussrundungsradius
    float _c;            // Kopfspiel-Faktor

    float _m;            // Modul
    float _x;            // Profilverschiebungsfaktor
    float _k;            // Kopfkuerzungsfaktor

    int _z;              // Zaehnezahl

    struct
    {
        float d;    // Waelzkreisdurchmesser
        float d_a;  // Aussendurchmesser
        float d_b;  // Basiskreisdurchmesser
        float d_f;  // Fusskreisdurchmesser

        float d_max; // Maximaler Aussendurchmesser
    } durchmesser;

public:
    Zahnraddaten(float alpha, float rho, float c, float m, float x, float k, int z);

    void setAlpha(float alpha);
    void setRho(float rho);
    void setC(float c);
    void setM(float m);
    void setX(float x);
    void setK(float k);
    void setZ(int z);

    float alpha(void);
    float rho(void);
    float c(void);
    float m(void);
    float x(void);
    float k(void);
    int z(void);

    float diameter(void);
    float diameter_outer(void);
    float diameter_base(void);
    float diameter_foot(void);
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
    virtual ~Zahnrad(void) { }

    void rotate(float deg);
    void move(float x, float y);

    void resetIterator(void);
    bool iteratorEndReached(void);
    float getNextX(void);
    float getNextY(void);

    float getDiameter(void);
    float getFootdiameter(void);
    float getBasediameter(void);
    float getOuterdiameter(void);
    int getToothcount(void);
    Zahnraddaten getGearwheelData(void);
};

#endif // ZAHNRAD_H

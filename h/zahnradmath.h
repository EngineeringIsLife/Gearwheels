#ifndef ZAHNRADMATH_H
#define ZAHNRADMATH_H

/*class ZahnradMath
{
public:
    ZahnradMath();
};*/

#include "zahnradprofil.h"
#include "zahnrad.h"

class ProfilMathematisch
{
private:


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
    Zahnraddaten zahnrad; // TODO: Move to private
    int parts_per_tooth;
    int parts_per_flank;

    Profile zahnprofil;
    ProfilMathematisch(Zahnraddaten zahnrad, int genauigkeit);

    void rotateGearwheel(float deg);
    void moveGearwheel(float x, float y);

    void resetIterator(void);
    bool iteratorEndReached(void);
    float getNextX(void);
    float getNextY(void);

    void rotateToFlankPoint(void);
};

#endif // ZAHNRADMATH_H

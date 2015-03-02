#ifndef ZAHNRADMATH_H
#define ZAHNRADMATH_H

#include "zahnrad.h"

class ProfilMathematisch : public Zahnrad
{
private:
    float phi_min;
    float phi_max;
    float limits[4];
    int steps;

    void calcProfile(void);
    void calcLimits(void);
    void calcLeftFlank(void);
    void calcHead(void);
    void calcRightFlank(void);
    void calcFullXY(void);
    void calcFoot(void);

public:
    int parts_per_tooth;
    int parts_per_flank;

    ProfilMathematisch(Zahnraddaten zahnrad, int profilepoints);
    virtual ~ProfilMathematisch(void) { }

    void rotateToFlankPoint(void);
    void changeToothcount(int z);
};

#endif // ZAHNRADMATH_H

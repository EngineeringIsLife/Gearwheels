#ifndef ZAHNRADMATH_H
#define ZAHNRADMATH_H

/*class ZahnradMath
{
public:
    ZahnradMath();
};*/

class ProfilMathematisch
{
private:
    Zahnraddaten zahnrad;

    int genauigkeit;

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
    int parts_per_tooth;
    int parts_per_flank;

    Zahnradprofil zahnprofil;
    ProfilMathematisch(Zahnraddaten zahnrad, int genauigkeit);

    void resetIterator(void);
    bool iteratorEndReached(void);
    float getNextX(void);
    float getNextY(void);
};

#endif // ZAHNRADMATH_H

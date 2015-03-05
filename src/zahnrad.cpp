#include <math.h>
#include "zahnrad.h"

#define DEG (M_PI/180.0)

Zahnraddaten::Zahnraddaten(float alpha, float rho, float c, float m, float x, float k, int z)
    : itersteps(10), _alpha(alpha), _rho(rho), _c(c), _m(m), _x(x), _k(k), _z(z)
{
    calcDurchmesser();
}

void Zahnraddaten::calcDurchmesser(void)
{
    float h = 0; // TODO: ??
    float h_a = _m * (1 + _x - h);
    float h_f = _m * (1 - _x + _c);

    durchmesser.d = _m * _z;
    durchmesser.d_a = durchmesser.d + 2 * h_a;
    durchmesser.d_b = durchmesser.d * cos(_alpha * DEG);
    durchmesser.d_f = durchmesser.d - 2 * h_f;

    // Schnittpunkt der Evolventen:
    float s = _m * (M_PI_2 + 2 * _x * tan(_alpha * DEG));
    float inv_a = s / durchmesser.d + tan(_alpha * DEG) - _alpha * DEG;
    float alpha_strich = pow(3 * inv_a, 1.0/3.0);

    // Iteration (siehe Wikipedia)
    for (int i = 0; i < itersteps; i++)
        alpha_strich += ((alpha_strich + inv_a) / tan(alpha_strich) - 1) / tan(alpha_strich);

    durchmesser.d_max = durchmesser.d * cos(_alpha * DEG) / cos(alpha_strich);
    if (durchmesser.d_max < durchmesser.d_a)
        durchmesser.d_a = durchmesser.d_max;
}

void Zahnraddaten::setAlpha(float alpha) { _alpha = alpha; calcDurchmesser(); }
void Zahnraddaten::setRho(float rho) { _rho = rho; }
void Zahnraddaten::setC(float c) { _c = c; }
void Zahnraddaten::setM(float m) { _m = m; calcDurchmesser(); }
void Zahnraddaten::setX(float x) { _x = x; calcDurchmesser(); }
void Zahnraddaten::setK(float k) { _k = k; }
void Zahnraddaten::setZ(int z) { _z = z; calcDurchmesser(); }

float Zahnraddaten::alpha(void) { return _alpha; }
float Zahnraddaten::rho(void) { return _rho; }
float Zahnraddaten::c(void) { return _c; }
float Zahnraddaten::m(void) { return _m; }
float Zahnraddaten::x(void) { return _x; }
float Zahnraddaten::k(void) { return _k; }
int Zahnraddaten::z(void) { return _z; }

float Zahnraddaten::diameter(void) { return durchmesser.d; }
float Zahnraddaten::diameter_outer(void) { return durchmesser.d_a; }
float Zahnraddaten::diameter_base(void) { return durchmesser.d_b; }
float Zahnraddaten::diameter_foot(void) { return durchmesser.d_f; }

Zahnrad::Zahnrad(Zahnraddaten zahnrad, int profile_size)
    : zahnrad(zahnrad), profilepoints(profile_size), zahnprofil(profile_size)
{ }

void Zahnrad::resetIterator(void) { zahnprofil.resetIterator(); }
bool Zahnrad::iteratorEndReached(void) { return zahnprofil.iteratorEndReached(); }
float Zahnrad::getNextX(void) { return zahnprofil.getNextX(); }
float Zahnrad::getNextY(void) { return zahnprofil.getNextY(); }

float Zahnrad::getDiameter(void) { return zahnrad.diameter(); }
float Zahnrad::getFootdiameter(void) { return zahnrad.diameter_foot(); }
float Zahnrad::getBasediameter(void) { return zahnrad.diameter_base(); }
float Zahnrad::getOuterdiameter(void) { return zahnrad.diameter_outer(); }

int Zahnrad::getToothcount(void) { return zahnrad.z(); }
Zahnraddaten Zahnrad::getGearwheelData(void) { return zahnrad; }

void Zahnrad::rotate(float deg)
{
    zahnprofil.rotate(deg);
}

void Zahnrad::move(float x, float y)
{
    zahnprofil.move(x,y);
}

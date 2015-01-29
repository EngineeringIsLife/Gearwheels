#include <math.h>
#include "zahnrad.h"

#define DEG (M_PI/180.0)

Zahnraddaten::Zahnraddaten(float alpha, float rho, float c, float m, float x, float k, int z)
    : alpha(alpha), rho(rho), c(c), m(m), x(x), k(k), z(z)
{
    itersteps = 10;
    calcDurchmesser();
}

void Zahnraddaten::calcDurchmesser(void)
{
    float h = 0; // TODO: ??
    float h_a = m * (1 + x - h);
    float h_f = m * (1 - x + c);

    durchmesser.d = m * z;
    durchmesser.d_a = durchmesser.d + 2 * h_a;
    durchmesser.d_b = durchmesser.d * cos(alpha * DEG);
    durchmesser.d_f = durchmesser.d - 2 * h_f;

    // Schnittpunkt der Evolventen:
    float s = m * (M_PI_2 + 2 * x * tan(alpha * DEG));
    float inv_a = s / durchmesser.d + tan(alpha * DEG) - alpha * DEG;
    float alpha_strich = pow(3 * inv_a, 1.0/3.0);

    // Iteration (siehe Wikipedia)
    for (int i = 0; i < itersteps; i++)
        alpha_strich += ((alpha_strich + inv_a) / tan(alpha_strich) - 1) / tan(alpha_strich);

    durchmesser.d_max = durchmesser.d * cos(alpha * DEG) / cos(alpha_strich);
    if (durchmesser.d_max < durchmesser.d_a)
        durchmesser.d_a = durchmesser.d_max;
}

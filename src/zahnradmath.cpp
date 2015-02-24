#include <math.h>
#include <iostream>

#include "zahnradfertigung.h"
#include "zahnradprofil.h"
#include "zahnrad.h"
#include "zahnradmath.h"

/* --------------- Mathematische errechnetes Zahnradprofil ------------- */

ProfilMathematisch::ProfilMathematisch(Zahnraddaten zahnrad, int genauigkeit)
    : zahnrad(zahnrad), zahnprofil(zahnrad.z * (genauigkeit - genauigkeit % 4 + 4))//, genauigkeit(genauigkeit)
{
    // Pruefe, ob Zahnfuss ueber Basisdurchmesser:
    phi_max = sqrt(zahnrad.durchmesser.d_a * zahnrad.durchmesser.d_a / (zahnrad.durchmesser.d_b * zahnrad.durchmesser.d_b) - 1);
    if (zahnrad.durchmesser.d_b < zahnrad.durchmesser.d_f)      // Zahnflanke beginnt auf Fusskreis
        phi_min = sqrt(zahnrad.durchmesser.d_f * zahnrad.durchmesser.d_f / (zahnrad.durchmesser.d_b * zahnrad.durchmesser.d_b) - 1);
    else                // Zahnflanke beginnt auf Basiskreis
        phi_min = 0;

    parts_per_tooth = genauigkeit - genauigkeit % 4 + 4;
    parts_per_flank = parts_per_tooth / 4;

    calcProfile();
}

void ProfilMathematisch::calcProfile(void)
{
    calcLimits();
    calcLeftFlank();
    calcHead();
    calcRightFlank();
    calcFoot();
    calcFullXY();
}

void ProfilMathematisch::calcLeftFlank(void)
{
    // Linke Zahnflanke
    for (int i = 0; i < parts_per_flank; i++)
    {
        float alpha = i * (phi_max - phi_min) / parts_per_flank + phi_min; // TODO: Andere Bezeichnung
        float x = (cos(alpha) + alpha * sin(alpha)) * zahnrad.durchmesser.d_b / 2;
        float y = (sin(alpha) - alpha * cos(alpha)) * zahnrad.durchmesser.d_b / 2;

        zahnprofil.setCartesian(i, x, y);
        //zahnprofil.setPolar(i, zahnrad.durchmesser.d_b/2, -alpha);
    }
}

void ProfilMathematisch::calcHead(void)
{
    for (int i = 0; i < parts_per_flank; i++)
    {
        float alpha = 4 * (limits[1] - limits[0]) / parts_per_tooth * i + limits[0];
        zahnprofil.setPolar(i + parts_per_flank, zahnrad.durchmesser.d_a / 2, alpha);
    }
}

void ProfilMathematisch::calcRightFlank(void)
{
    for (int i = 0; i < parts_per_flank; i++)
    {
        float alpha = -i * (phi_max - phi_min) / parts_per_flank - phi_min;

        // Koordinatentransformation
        float x = (cos(alpha) + alpha * sin(alpha)) * zahnrad.durchmesser.d_b / 2;
        float y = (sin(alpha) - alpha * cos(alpha)) * zahnrad.durchmesser.d_b / 2;

        float phi = atan2(y,x);
        float r = sqrt(x*x + y*y);

        zahnprofil.setCartesian(3 * parts_per_flank - 1 - i, cos(limits[2] + phi) * r, sin(limits[2] + phi) * r);
    }
}

void ProfilMathematisch::calcFoot(void)
{
    /* Two possibilities:
     *  Basiskreis groesser Fusskreis: Fussflanke als Bogen Evolventenanfangspunkt zu
     *  Evolventenanfangspunkt mit Tangente auf Fusskreis
     * oder
     *  Fusskreis groesser Basiskreis: Fusskreis als Fussflanke */
    if (zahnrad.durchmesser.d_b > zahnrad.durchmesser.d_f)
    {
        //std::cout << "Methode 1" << std::endl;
        // 3 Punkte des Kreisbogens
        float x1 = cos(limits[2]) * zahnrad.durchmesser.d_b / 2;
        float y1 = sin(limits[2]) * zahnrad.durchmesser.d_b / 2;

        float x2 = cos((limits[3] - limits[2]) / 2 + limits[2]) * zahnrad.durchmesser.d_f / 2;
        float y2 = sin((limits[3] - limits[2]) / 2 + limits[2]) * zahnrad.durchmesser.d_f / 2;

        float x3 = cos(limits[3]) * zahnrad.durchmesser.d_b / 2;
        float y3 = sin(limits[3]) * zahnrad.durchmesser.d_b / 2;

        // Mittelpunkt des Kreisbogens und aufgespannter Winkel
        float x_M = (x1 * x1 - x3 * x3 + y1 * y1 - y3 * y3 \
                    - ((y1 - y3) / (y1 - y2) * (x1 * x1 - x2 * x2 + y1 * y1-y2*y2))) \
                    / (2 * (x1 - x3) - 2 * ((y1 - y3) / (y1 - y2)) * (x1 - x2));
        float y_M = (x1 * x1 - x2 * x2 + y1 * y1 - y2 * y2 - 2 * x_M * (x1 - x2)) \
                    / (2 * (y1 - y2));
        float d_M = sqrt((x1 - x_M) * (x1 - x_M) + (y1 - y_M) * (y1 - y_M));

        float phi_start = atan2(y3 - y_M, x3 - x_M);
        float phi_end = atan2(y1 - y_M, x_M - x1);

        for (int i = 0; i < parts_per_flank; i++)   // Zahnfuss berechnen
        {
            float alpha = 4.0 * (M_PI - (phi_start + phi_end)) / parts_per_tooth * i + phi_start;

            float x = cos(alpha) * d_M;
            float y = sin(alpha) * d_M;

            zahnprofil.setCartesian(parts_per_tooth - 1 - i, x + x_M, y + y_M);
        }
    }

    else
    {
        // Endpunkte der Evolventen auf dem Fusskreis
        float gamma = 360.0 / zahnrad.z;
        limits[2] = atan2(zahnprofil.getY(parts_per_flank*3 - 1), zahnprofil.getX(parts_per_flank*3 - 1));
        limits[3] = atan2(zahnprofil.getY(0), zahnprofil.getX(0)) + gamma * DEG;

        for (int i = 0; i < parts_per_flank; i++)   // Zahnfuß
        {
            float alpha = 4.0 * (limits[3] - limits[2]) / parts_per_tooth * i + limits[2];

            float x = cos(alpha) * zahnrad.durchmesser.d_f / 2;
            float y = sin(alpha) * zahnrad.durchmesser.d_f / 2;

            zahnprofil.setCartesian(parts_per_flank * 3 + i, x, y);
        }
    }
}

void ProfilMathematisch::calcFullXY(void)
{
    float gamma = 360.0 / zahnrad.z;
    for (int j = 1; j < zahnrad.z; j++)
    {
        for (int i = 0; i < parts_per_tooth; i++)
        {
            float x = zahnprofil.getX(i);
            float y = zahnprofil.getY(i);

            // Rotation
            zahnprofil.setCartesian(i + j * parts_per_tooth, cos(gamma * j * DEG) * x - sin(gamma * j * DEG) * y, sin(gamma * j * DEG) * x + cos(gamma * j * DEG) * y);
        }
    }
    rotateToFlankPoint();
}

void ProfilMathematisch::rotateGearwheel(float deg)
{
    zahnprofil.rotate(deg);
}

void ProfilMathematisch::moveGearwheel(float x, float y)
{
    zahnprofil.move(x,y);
}

// Grenzen des viergeteilten Zahns
void ProfilMathematisch::calcLimits(void)
{
    float gamma = 360.0 / zahnrad.z;
    float s = zahnrad.m * (M_PI_2 + 2 * zahnrad.x * tan(zahnrad.alpha * DEG));

    /* 4 Parts: 0 - Ende linke Flanke
     *          1 - Ende Zahnkopf
     *          2 - Ende rechte Flanke
     *          3 - Ende Zahnfuss / Ende Zahn */

    // Winkel der Evolvente am Waelzkreis
    float phi = sqrt(zahnrad.durchmesser.d * zahnrad.durchmesser.d / (zahnrad.durchmesser.d_b * zahnrad.durchmesser.d_b) - 1);
    float x = (cos(phi) + phi * sin(phi)) * zahnrad.durchmesser.d_b / 2;
    float y = (sin(phi) - phi * cos(phi)) * zahnrad.durchmesser.d_b / 2;
    float beta = atan2(y,x);

    limits[0] = atan2((sin(phi_max) - phi_max * cos(phi_max)) * zahnrad.durchmesser.d_b / 2,
            (cos(phi_max) + phi_max * sin(phi_max)) * zahnrad.durchmesser.d_b / 2);
    limits[2] = 2 * beta + 2 * s / zahnrad.durchmesser.d;
    limits[1] = limits[2] - limits[0];
    limits[3] = gamma * DEG;
}

void ProfilMathematisch::rotateToFlankPoint(void)
{
    // Find best match for a point on flank that hits the diameter
    int i = 0;
    while (zahnprofil.getLength(i) < zahnrad.durchmesser.d/2 && i < parts_per_flank)
    {
        i++;
    }

    float diff = zahnrad.durchmesser.d / 2 - zahnprofil.getLength(i-1);
    diff /= zahnprofil.getLength(i) - zahnprofil.getLength(i-1);
    diff *= zahnprofil.getAngle(i) - zahnprofil.getAngle(i-1);

    zahnprofil.rotateRad(-zahnprofil.getAngle(i-1)-diff);
}

void ProfilMathematisch::resetIterator(void) { zahnprofil.resetIterator(); }
bool ProfilMathematisch::iteratorEndReached(void) { return zahnprofil.iteratorEndReached(); }
float ProfilMathematisch::getNextX(void) { return zahnprofil.getNextX(); }
float ProfilMathematisch::getNextY(void) { return zahnprofil.getNextY(); }

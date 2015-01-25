#include <QCoreApplication>
#include <math.h>
#include <iostream>
#include "bezugsprofil.h"

#define DEG (M_PI/180.0)

void Bezugsprofil::calcBezugsprofil(void)
{
    const float alpha2 = 90 - zahnrad.alpha;
    float rho_f = zahnrad.rho * zahnrad.m;
    float h_a = zahnrad.m * (1 - zahnrad.k);
    float h_f = zahnrad.m * (1 + zahnrad.c);
    float s_p = M_PI_2 * zahnrad.m;
    float p = M_PI * zahnrad.m;
    float skalierung = genauigkeit / p;

    profil = (float *) calloc(genauigkeit + 1, sizeof(float));
    profilx = (float *) calloc(genauigkeit + 1, sizeof(float));

    // Linke Fussrundung
    float x_B = (h_f - rho_f * (1 - cos(alpha2 * DEG))) / tan(alpha2*DEG) + s_p;
    float x_M = x_B + rho_f * sin(alpha2 * DEG);

    // Rechte Fussrundung
    float x_B2 = - (h_f - rho_f * (1 - cos(alpha2 * DEG))) / tan(alpha2*DEG) + p;
    float x_M2 = x_B2 - rho_f * sin(alpha2 * DEG);

    /* Grenzen:
    *   0__1
    *   /  \
    *  /    \2
    *        \    /
    *         \__/
    *         3  4
    */

    float grenze[5];
    grenze[0] = (h_a / tan(alpha2 * DEG))        * skalierung;
    grenze[1] = (s_p - h_a / tan(alpha2 * DEG))  * skalierung;
    grenze[2] = s_p                              * skalierung;
    grenze[3] = x_B                              * skalierung;
    grenze[4] = x_B2                             * skalierung;

    float grenze_rundung1 = x_M                  * skalierung;
    float grenze_rundung2 = x_M2                 * skalierung;

    for (int i = 0; i < genauigkeit; i++)
    {
        // Algorithmus fuer Bezugsprofil
        float x = i / skalierung;

        if      (i < grenze[0]) profil[i] = tan(alpha2 * DEG) * x;
        else if (i < grenze[1]) profil[i] = h_a;
        else if (i < grenze[3]) profil[i] = -tan(alpha2 * DEG) * x + tan(alpha2 * DEG) * s_p;
        else if (i < grenze[4]) {
            if (i < grenze_rundung1) profil[i] = rho_f - h_f - rho_f * cos(asin((x_M - x)/rho_f));    // Fussbereich unterteilt in Rundungsbereich und Gerade
            else if (i < grenze_rundung2) profil[i] = -h_f;
            else profil[i] = rho_f - h_f - rho_f * cos(asin((x - x_M2)/rho_f));
        }
        else profil[i] = tan(alpha2 * DEG) * x - tan(alpha2 * DEG) * p;

        profilx[i] = x;

        //cout << i << ": " << (x_M-x)/rho_f << " " << profilx[i] << " " << profil[i] << endl;
    }

    //cout << "Bezugsprofil fertig" << endl;
    profilx[genauigkeit] = p;
    profil[genauigkeit] = 0;
}

Bezugsprofil::~Bezugsprofil(void)
{
    free(profil);
    free(profilx);
}

void Bezugsprofil::printProfile(std::ostream &stream)
{
    for (int i = 0; i < genauigkeit; i++)
    {
        stream << profilx[i] << " " << profil[i] << std::endl;
    }
}

void Bezugsprofil::printProfileToMatlab(std::ostream &stream)
{
    stream << "profil = [" << std::endl;
    for (int i = 0; i < genauigkeit-1; i++)
    {
        stream << profilx[i] << ", " << profil[i] << ";" << std::endl;
    }
    stream << profilx[genauigkeit-1] << ", " << profil[genauigkeit-1] << "];";
}

Zahnradprofil::Zahnradprofil(int elemente)
    : elemente(elemente)
{
    std::cout << "Berechnete Elemente Konstruktor: " << elemente << std::endl;
    winkel = (float*)calloc(elemente, sizeof(float));
    laenge = (float*)calloc(elemente, sizeof(float));
}

Zahnradprofil::~Zahnradprofil(void)
{
    free(winkel);
    free(laenge);
}

void Zahnradprofil::setX(int pos_id, float x)
{
    // TODO: Index pruefen und Umrechnung in Polarkoordinaten
    if (pos_id >= elemente)
    {
        std::cout << "Fehler beim Setzen von x. ID: " << pos_id << " - Value: " << x << std::endl;
        return;
    }
    winkel[pos_id] = x;
}

void Zahnradprofil::setY(int pos_id, float y)
{
    // TODO: Index pruefen und Umrechnung in Polarkoordinaten
    if (pos_id >= elemente)
    {
        std::cout << "Fehler beim Setzen von y. ID: " << pos_id << " - Value: " << y << std::endl;
        return;
    }
    laenge[pos_id] = y;
}

float Zahnradprofil::getX(int pos_id)
{
    return winkel[pos_id];
}

float Zahnradprofil::getY(int pos_id)
{
    return laenge[pos_id];
}

/* --------------- Mathematisches Profil ------------- */

ProfilMathematisch::ProfilMathematisch(Zahnrad zahnrad, int genauigkeit)
    : zahnrad(zahnrad), zahnprofil(zahnrad.z * (genauigkeit - genauigkeit % 4 + 4)), genauigkeit(genauigkeit)
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
    //float h = 0; // TODO: ??

    //float p = M_PI * zahnrad.m;

    std::cout << "Berechnete Teile: " << parts_per_tooth << std::endl;
    //zahnprofil.elemente = zahnrad.z * parts_per_tooth;
    std::cout << "Berechnete Elemente Zahnrad: " << zahnprofil.elemente << std::endl;

    calcLimits();
    std::cout << "Beginne linke Flanke" << std::endl;
    calcLeftFlank();
    std::cout << "Beginne Kopf" << std::endl;
    calcHead();
    std::cout << "Beginne rechte Flanke" << std::endl;
    calcRightFlank();
    std::cout << "Beginne Fuss" << std::endl;
    calcFoot();
    std::cout << "Beginne Kopie" << std::endl;
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

        zahnprofil.setX(i, x);
        zahnprofil.setY(i, y);
    }
}

void ProfilMathematisch::calcHead(void)
{
    for (int i = 0; i < parts_per_flank; i++)
    {
        float alpha = 4 * (limits[1] - limits[0]) / parts_per_tooth * i + limits[0];
        float x = cos(alpha) * zahnrad.durchmesser.d_a / 2;
        float y = sin(alpha) * zahnrad.durchmesser.d_a / 2;

        zahnprofil.setX(i + parts_per_flank, x);
        zahnprofil.setY(i + parts_per_flank, y);
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

        zahnprofil.setX(3 * parts_per_flank - 1 - i, cos(limits[2] + phi) * r);
        zahnprofil.setY(3 * parts_per_flank - 1 - i, sin(limits[2] + phi) * r);
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

            zahnprofil.setX(parts_per_tooth - 1 - i, x + x_M);
            zahnprofil.setY(parts_per_tooth - 1 - i, y + y_M);
        }
    }

    else
    {
        //std::cout << "Methode 2" << std::endl;
        // Endpunkte der Evolventen auf dem Fusskreis
        float gamma = 360.0 / zahnrad.z;
        limits[2] = atan2(zahnprofil.getY(parts_per_flank*3 - 1), zahnprofil.getX(parts_per_flank*3 - 1));
        limits[3] = atan2(zahnprofil.getY(0), zahnprofil.getX(0)) + gamma * DEG;

        for (int i = 0; i < parts_per_flank; i++)   // Zahnfuß
        {
            float alpha = 4.0 * (limits[3] - limits[2]) / parts_per_tooth * i + limits[2];

            float x = cos(alpha) * zahnrad.durchmesser.d_f / 2;
            float y = sin(alpha) * zahnrad.durchmesser.d_f / 2;

            zahnprofil.setX(parts_per_flank * 3 + i, x);
            zahnprofil.setY(parts_per_flank * 3 + i, y);
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
            zahnprofil.setX(i + j * parts_per_tooth, cos(gamma * j * DEG) * x - sin(gamma * j * DEG) * y);
            zahnprofil.setY(i + j * parts_per_tooth, sin(gamma * j * DEG) * x + cos(gamma * j * DEG) * y);
        }
    }
}

// Grenzen des viergeteilten Zahns
void ProfilMathematisch::calcLimits(void)
{
    //float h_a = zahnrad.m * (1 + zahnrad.x - h);
    //float h_f = zahnrad.m * (1 - zahnrad.x + zahnrad.c);

    float gamma = 360.0 / zahnrad.z;
    //float phi_max = sqrt(zahnrad.durchmesser.d_a * zahnrad.durchmesser.d_a / (zahnrad.durchmesser.d_b * zahnrad.durchmesser.d_b) - 1);

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

void ProfilMathematisch::printProfile(std::ostream &stream)
{
    // TODO: Auf komplettes Profil anpassen (2 entfernen)
    std::cout << parts_per_tooth << std::endl;
    for (int i = 0; i < parts_per_tooth; i++)
    {
        stream << zahnprofil.getX(i) << " " << zahnprofil.getY(i) << std::endl;
    }
}

void ProfilMathematisch::printProfileToMatlab(std::ostream &stream)
{
    stream << "profil = [" << std::endl;
    for (int i = 0; i < parts_per_tooth*zahnrad.z - 1; i++)
         stream << zahnprofil.getX(i) << ", " << zahnprofil.getY(i) << ";" << std::endl;
    stream << zahnprofil.getX(parts_per_tooth - 1) << ", " << zahnprofil.getY(parts_per_tooth - 1) << "];";
}

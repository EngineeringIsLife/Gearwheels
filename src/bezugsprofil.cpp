#include <QCoreApplication>
#include <math.h>
#include <iostream>
#include "bezugsprofil.h"

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
    iteratX = -1;
    iteratY = -1;
}

Zahnradprofil::Zahnradprofil(Zahnradprofil& rhs)
{
    elemente = rhs.elemente;
    winkel = (float*)calloc(elemente, sizeof(float));
    laenge = (float*)calloc(elemente, sizeof(float));
    iteratX = -1;
    iteratY = -1;

    rhs.resetIterator();
    int i = 0;
    while(!rhs.iteratorEndReached())
    {
        // TODO: Einsetzen sobald vorhanden
        //profil.setCartesian(i++, rhs.getNextX(), rhs.getNextY());
        setX(i, rhs.getNextX());
        setY(i++, rhs.getNextY());
    }
}

Zahnradprofil::~Zahnradprofil(void)
{
    free(winkel);
    free(laenge);
}

void Zahnradprofil::setX(int pos_id, float x)
{
    // TODO: Index pruefen und Umrechnung in Polarkoordinaten / Exception werfen
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

// TODO: Aendern
float Zahnradprofil::getX(int pos_id)
{
    return winkel[pos_id];
}

float Zahnradprofil::getY(int pos_id)
{
    return laenge[pos_id];
}

void Zahnradprofil::resetIterator(void)
{
    iteratX = 0;
    iteratY = 0;
}

bool Zahnradprofil::iteratorEndReached(void)
{
    if (iteratX >= elemente || iteratY >= elemente)
        return true;
    else
        return false;
}

float Zahnradprofil::getNextX(void)
{
    if (iteratX < elemente)
        return getX(iteratX++);
    else
    {
        iteratX++;
        // TODO: Exception
        return -1;
    }
}

float Zahnradprofil::getNextY(void)
{
    if (iteratY < elemente)
    {
        return getY(iteratY++);
    }
    else
    {
        iteratY++;
        // TODO: Exception
        return -1;
    }
}

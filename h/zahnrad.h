#ifndef ZAHNRAD_H
#define ZAHNRAD_H

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
        float d_b;  // Basiskreisdurchmesser (?)
        float d_f;  // Fusskreisdurchmesser

        float d_max; // Maximaler Aussendurchmesser
    } durchmesser;

    Zahnraddaten(float alpha, float rho, float c, float m, float x, float k, int z);

};

#endif // ZAHNRAD_H

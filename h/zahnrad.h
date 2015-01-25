#ifndef ZAHNRAD_H
#define ZAHNRAD_H

class Zahnrad
{
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

    Zahnrad(float alpha, float rho, float c, float m, float x, float k, int z)
        : alpha(alpha), rho(rho), c(c), m(m), x(x), k(k), z(z) { calcDurchmesser(); }

private:
    void calcDurchmesser(void);

};

#endif // ZAHNRAD_H

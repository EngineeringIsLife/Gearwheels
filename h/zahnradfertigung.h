#ifndef ZAHNRADFERTIGUNG_H
#define ZAHNRADFERTIGUNG_H

#include "zahnrad.h"

class ZahnradFertigung : public Zahnrad
{
private:
    float schrittweite; // Rechenschrittweite - evtl in anderer funktion besser aufgehoben
    void calcProfile(void);

public:
    ZahnradFertigung(Zahnraddaten zahnrad, float schrittweite, int profilepoints);
};

#endif

#ifndef GEARWHEELOUTPUT_H
#define GEARWHEELOUTPUT_H

class GearwheelOutput
{
private:
    Profil& profil;

public:
    GearwheelOutput(Profil& profile);

    void printProfile(std::ostream &stream);
    void printProfileToMatlab(std::ostream &stream);
};

#endif // GEARWHEELOUTPUT_H

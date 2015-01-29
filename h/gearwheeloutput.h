#ifndef GEARWHEELOUTPUT_H
#define GEARWHEELOUTPUT_H

class GearwheelOutput
{
private:
    Zahnradprofil& profil;

public:
    GearwheelOutput(Zahnradprofil& profile);

    void printProfile(std::ostream &stream);
    void printProfileToMatlab(std::ostream &stream);
};

#endif // GEARWHEELOUTPUT_H

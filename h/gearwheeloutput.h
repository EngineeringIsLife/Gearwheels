#ifndef GEARWHEELOUTPUT_H
#define GEARWHEELOUTPUT_H

class GearwheelOutput
{
protected:
    Profil& profil;

public:
    GearwheelOutput(Profil& profile);

    void printProfile(std::ostream &stream);
    void printProfileToMatlab(std::ostream &stream);
};


class GearwheelOutputQt : public GearwheelOutput
{
public:
    GearwheelOutputQt(Profil& profile) : GearwheelOutput(profile) { }
    void printToDisplay(QPainter& painter, int center_x, int center_y, float scale);
};

#endif // GEARWHEELOUTPUT_H

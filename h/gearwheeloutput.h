#ifndef GEARWHEELOUTPUT_H
#define GEARWHEELOUTPUT_H

class GearwheelOutput
{
protected:
    Profile& profil;

public:
    GearwheelOutput(Profile& profile);

    void printProfile(std::ostream &stream);
    void printProfileToMatlab(std::ostream &stream);
};


class GearwheelOutputQt : public GearwheelOutput
{
public:
    GearwheelOutputQt(Profile& profile) : GearwheelOutput(profile) { }
    void printToDisplay(QPainter& painter, int center_x, int center_y, float scale);
};

#endif // GEARWHEELOUTPUT_H

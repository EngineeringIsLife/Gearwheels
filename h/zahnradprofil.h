#ifndef ZAHNRADPROFIL_H
#define ZAHNRADPROFIL_H

struct PointsPolar
{
    float angle_;
    float length_;
};

struct PointsCartesian
{
    float x;
    float y;
};

class Profil
{
private:
    PointsPolar *points;

    int iteratX, iteratY;

    struct PointsCartesian polarToCartesian(float length, float angle);
    struct PointsCartesian polarToCartesian(struct PointsPolar in);
    struct PointsPolar cartesianToPolar(float x, float y);
    struct PointsPolar cartesianToPolar(struct PointsCartesian in);

public:
    Profil(int elemente);
    Profil(Profil& rhs);
    ~Profil(void);

    int elemente;

    void setCartesian(int pos_id, float x, float y);
    void setPolar(int pos_id, float length, float angle);

    void setAngle(int pos_id, float angle);
    void setLength(int pos_id, float length);

    float getAngle(int pos_id);
    float getLength(int pos_id);
    float getX(int pos_id);
    float getY(int pos_id);

    void resetIterator(void);
    bool iteratorEndReached(void);
    float getNextX(void);
    float getNextY(void);
};

#endif // ZAHNRADPROFIL_H

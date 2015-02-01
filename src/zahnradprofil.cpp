#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "zahnradprofil.h"
//#include "bezugsprofil.h"

Profil::Profil(int elemente)
    : elemente(elemente)
{
    std::cout << "Berechnete Elemente Konstruktor: " << elemente << std::endl;
    points = (struct PointsPolar*)calloc(elemente, sizeof(struct PointsPolar));
    iteratX = -1;
    iteratY = -1;
}

Profil::Profil(Profil& rhs)
{
    elemente = rhs.elemente;
    points = (struct PointsPolar*)calloc(elemente, sizeof(struct PointsPolar));
    iteratX = -1;
    iteratY = -1;

    rhs.resetIterator();
    int i = 0;
    while(!rhs.iteratorEndReached())
    {
        // TODO: Einsetzen sobald vorhanden
        rhs.setCartesian(i++, rhs.getNextX(), rhs.getNextY());
        //setX(i, rhs.getNextX());
        //setY(i++, rhs.getNextY());
    }
}

Profil::~Profil(void)
{
    //free(angle_);
    //free(length_);
    free(points);
}

void Profil::setCartesian(int pos_id, float x, float y)
{
    points[pos_id] = cartesianToPolar(x, y);
}

void Profil::setPolar(int pos_id, float length, float angle)
{
    points[pos_id].angle_ = angle;
    points[pos_id].length_ = length;
}

void Profil::setLength(int pos_id, float length)
{
    if (pos_id >= elemente)
    {
        // throw exception
        return;
    }
    points[pos_id].length_ = length;
}

void Profil::setAngle(int pos_id, float angle)
{
    if (pos_id >= elemente)
    {
        // throw exception
        return;
    }
    points[pos_id].angle_ = angle;
}

float Profil::getX(int pos_id)
{
    PointsCartesian temp = polarToCartesian(points[pos_id]);
    return temp.x;
}

float Profil::getY(int pos_id)
{
    PointsCartesian temp = polarToCartesian(points[pos_id]);
    return temp.y;
}

float Profil::getAngle(int pos_id)
{
    return points[pos_id].angle_;
}

float Profil::getLength(int pos_id)
{
    return points[pos_id].length_;
}

void Profil::resetIterator(void)
{
    iteratX = 0;
    iteratY = 0;
}

bool Profil::iteratorEndReached(void)
{
    if (iteratX >= elemente || iteratY >= elemente)
        return true;
    else
        return false;
}

float Profil::getNextX(void)
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

float Profil::getNextY(void)
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


struct PointsCartesian Profil::polarToCartesian(float length, float angle)
{
    struct PointsPolar pol;
    pol.angle_ = angle;
    pol.length_ = length;
    return polarToCartesian(pol);
}

struct PointsCartesian Profil::polarToCartesian(struct PointsPolar in)
{
    struct PointsCartesian out;
    out.x = in.length_ * cos(in.angle_);
    out.y = in.length_ * sin(in.angle_);
    return out;
}

struct PointsPolar Profil::cartesianToPolar(float x, float y)
{
    struct PointsCartesian cart;
    cart.x = x;
    cart.y = y;
    return cartesianToPolar(cart);
}

struct PointsPolar Profil::cartesianToPolar(struct PointsCartesian in)
{
    struct PointsPolar out;
    out.length_ = sqrt(in.x*in.x + in.y*in.y);
    if (in.y >= 0)
        out.angle_ = acos(in.x / out.length_);
    else
        out.angle_ = -acos(in.x / out.length_);
    return out;
}

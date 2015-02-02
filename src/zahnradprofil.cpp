#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include "zahnradprofil.h"

Profil::Profil(int elemente)
    : elemente(elemente)
{
    points = (struct PointsPolar*)calloc(elemente, sizeof(struct PointsPolar));
    iteratX = 0;
    iteratY = 0;
}

Profil::Profil(Profil& rhs)
    : Profil(rhs.elemente)
{
    rhs.resetIterator();
    int i = 0;
    while(!rhs.iteratorEndReached())
    {
        rhs.setCartesian(i++, rhs.getNextX(), rhs.getNextY());
    }
}

Profil::~Profil(void)
{
    free(points);
}

int Profil::getElementCount(void) { return elemente; }

void Profil::setCartesian(int pos_id, float x, float y)
{
    checkForIndexError(pos_id);
    points[pos_id] = cartesianToPolar(x, y);
}

void Profil::setPolar(int pos_id, float length, float angle)
{
    checkForIndexError(pos_id);
    points[pos_id].angle = angle;
    points[pos_id].length = length;
}

void Profil::setLength(int pos_id, float length)
{
    checkForIndexError(pos_id);
    points[pos_id].length = length;
}

void Profil::setAngle(int pos_id, float angle)
{
    checkForIndexError(pos_id);
    points[pos_id].angle = angle;
}

float Profil::getX(int pos_id)
{
    checkForIndexError(pos_id);
    return polarToCartesian(points[pos_id]).x;
}

float Profil::getY(int pos_id)
{
    checkForIndexError(pos_id);
    return polarToCartesian(points[pos_id]).y;
}

float Profil::getAngle(int pos_id)
{
    checkForIndexError(pos_id);
    return points[pos_id].angle;
}

float Profil::getLength(int pos_id)
{
    checkForIndexError(pos_id);
    return points[pos_id].length;
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
        return -1;
    }
}

struct PointsCartesian Profil::polarToCartesian(float length, float angle)
{
    struct PointsPolar pol;
    pol.angle = angle;
    pol.length = length;
    return polarToCartesian(pol);
}

struct PointsCartesian Profil::polarToCartesian(struct PointsPolar in)
{
    struct PointsCartesian out;
    out.x = in.length * cos(in.angle);
    out.y = in.length * sin(in.angle);
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
    out.length = sqrt(in.x*in.x + in.y*in.y);
    if (out.length == 0)
        out.angle = 0;
    else if (in.y >= 0)
        out.angle = acos(in.x / out.length);
    else
        out.angle = -acos(in.x / out.length);
    return out;
}

void Profil::checkForIndexError(int id)
{
    if (id < 0 || id >= elemente)
        throw std::out_of_range ("Index error: Out of range");
}

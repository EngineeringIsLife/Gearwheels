#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include "zahnradprofil.h"

Profile::Profile(int elemente)
    : elemente(elemente)
{
    points = (struct PointsPolar*)calloc(elemente, sizeof(struct PointsPolar));
    iteratX = 0;
    iteratY = 0;
}

Profile::Profile(Profile& rhs)
    : Profile(rhs.elemente)
{
    rhs.resetIterator();
    int i = 0;
    while(!rhs.iteratorEndReached())
    {
        rhs.setCartesian(i++, rhs.getNextX(), rhs.getNextY());
    }
}

Profile::~Profile(void)
{
    free(points);
}

void Profile::setSizeAndResetProfile(int elements)
{
    elemente = elements;
    points = (struct PointsPolar*)realloc(points, elemente*sizeof(struct PointsPolar));
}

int Profile::getElementCount(void) { return elemente; }

void Profile::setCartesian(int pos_id, float x, float y)
{
    checkForIndexError(pos_id);
    points[pos_id] = cartesianToPolar(x, y);
}

void Profile::setPolar(int pos_id, float length, float angle)
{
    checkForIndexError(pos_id);
    points[pos_id].angle = angle;
    points[pos_id].length = length;
}

void Profile::setLength(int pos_id, float length)
{
    checkForIndexError(pos_id);
    points[pos_id].length = length;
}

void Profile::setAngle(int pos_id, float angle)
{
    checkForIndexError(pos_id);
    points[pos_id].angle = angle;
}

float Profile::getX(int pos_id)
{
    checkForIndexError(pos_id);
    return polarToCartesian(points[pos_id]).x;
}

float Profile::getY(int pos_id)
{
    checkForIndexError(pos_id);
    return polarToCartesian(points[pos_id]).y;
}

float Profile::getAngle(int pos_id)
{
    checkForIndexError(pos_id);
    return points[pos_id].angle;
}

float Profile::getLength(int pos_id)
{
    checkForIndexError(pos_id);
    return points[pos_id].length;
}

void Profile::resetIterator(void)
{   
    iteratX = 0;
    iteratY = 0;
}

bool Profile::iteratorEndReached(void)
{
    if (iteratX >= elemente || iteratY >= elemente)
        return true;
    else
        return false;
}

float Profile::getNextX(void)
{
    checkForIndexError(iteratX);
    return getX(iteratX++);
}

float Profile::getNextY(void)
{
    checkForIndexError(iteratY);
    return getY(iteratY++);
}

float Profile::getNextLength()
{
    checkForIndexError(iteratLength);
    return getLength(iteratLength++);
}

float Profile::getNextAngle()
{
    checkForIndexError(iteratAngle);
    return getAngle(iteratAngle++);
}

struct PointsCartesian Profile::polarToCartesian(float length, float angle)
{
    struct PointsPolar pol;
    pol.angle = angle;
    pol.length = length;
    return polarToCartesian(pol);
}

struct PointsCartesian Profile::polarToCartesian(struct PointsPolar in)
{
    struct PointsCartesian out;
    out.x = in.length * cos(in.angle);
    out.y = in.length * sin(in.angle);
    return out;
}

struct PointsPolar Profile::cartesianToPolar(float x, float y)
{
    struct PointsCartesian cart;
    cart.x = x;
    cart.y = y;
    return cartesianToPolar(cart);
}

struct PointsPolar Profile::cartesianToPolar(struct PointsCartesian in)
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

struct PointsPolar Profile::getRotatedPolar(int id, float deg)
{
    struct PointsPolar temp;
    temp.length = getLength(id);
    temp.angle = getRotatedAngle(id, deg);
    return temp;
}

struct PointsCartesian Profile::getRotatedCartesian(int id, float deg)
{
    return polarToCartesian(getRotatedPolar(id, deg));
}

float Profile::getRotatedAngle(int id, float deg)
{
    return getAngle(id) + deg/2 * M_PI/180;
}

float Profile::getRotatedLength(int id, float deg)
{
    return getLength(id);
}

float Profile::getRotatedX(int id, float deg)
{
    return getRotatedCartesian(id, deg).x;
}

float Profile::getRotatedY(int id, float deg)
{
    return getRotatedCartesian(id, deg).y;
}

void Profile::rotate(float deg)
{
    for (int i = 0; i < elemente; i++)
    {
        setAngle(i, getAngle(i)+deg/2*M_PI/180);
    }
}

void Profile::rotateRad(float rad)
{
    for (int i = 0; i < elemente; i++)
    {
        setAngle(i, getAngle(i) + rad);
    }
}

void Profile::move(float x, float y)
{
    for (int i = 0; i < elemente; i++)
    {
        setCartesian(i, getX(i)+x, getY(i)+y);
    }
}

void Profile::mirror(void)
{
    for (int i = 0; i < elemente; i++)
    {
        setAngle(i, -1 * getAngle(i));
    }
}

void Profile::checkForIndexError(int id)
{
    if (id < 0 || id >= elemente)
        throw std::out_of_range ("Index error: Out of range");
}

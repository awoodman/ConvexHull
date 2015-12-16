#include "Point.h"

Point::Point(double x, double y):__x(x),__y(y) { idGen(); }


Point &Point::operator=(const Point& rhs) {
    if (*this == rhs) {
        return *this;
    }
    else {
        __x = rhs.__x;
        __y = rhs.__y;
        __id = rhs.__id;
        __angle = rhs.__angle;
    }
}

Point::~Point() { }

bool Point::operator<=(const Point &rhs) {
    bool decision;

    if (__x <= rhs.__x)
        decision = true;
    else
        return false;

    if (__y <= rhs.__y)
        decision = true;
    else
        return false;

    return decision;
}

bool Point::operator>=(const Point &rhs) {
    bool decision;

    if (__x >= rhs.__x)
        decision = true;
    else
        return false;

    if (__y >= rhs.__y)
        decision = true;
    else
        return false;

    return decision;
}

bool Point::operator<(const Point &rhs) {
    if (__x < rhs.__x)
        return true;
    else if (__x > rhs.__x)
        return false;
    else {
        if (__y < rhs.__y)
            return true;
        else
            return false;
    }
}

bool Point::operator>(const Point &rhs) {
    if (__x > rhs.__x)
        return true;
    else if (__x < rhs.__x)
        return false;
    else {
        if (__y > rhs.__y)
            return true;
        else
            return false;
    }
}

bool Point::operator==(const Point &rhs) {
    if (__id == rhs.__id)
        return true;
    else
        return false;
}

void Point::idGen() {
    static int id = 0;
    __id = id++;
}

void Point::setAng(double ang) {
    __angle = ang;
}

double Point::distTo(const Point& pt) {
    double dist = sqrt(pow((pt.getX()-__x),2)+pow((pt.getY()-__y),2));
    return dist;
}

#ifndef CONVEXHULL_POINT_H
#define CONVEXHULL_POINT_H

#include <cmath>

class Point {
private:
    double __x, __y;    // Coordinates
    int __id;           // ID
    double __angle;     // Angle from polar axis, about bottom point
    const int __dim = 2;
public:
    Point(double,double);
//    Point(const Point &);
    Point &operator=(const Point&);
    ~Point();

    void idGen();
    double getX() const { return __x; }
    double getY() const { return __y; }

    double getAng() const { return __angle; }
    void setAng(double);

    double distTo(const Point&);

    bool operator<=(const Point &);
    bool operator>=(const Point &);

    bool operator<(const Point &);
    bool operator>(const Point &);
    bool operator==(const Point &);
};


#endif //CONVEXHULL_POINT_H

#ifndef CONVEXHULL_CONVEXHULL_H
#define CONVEXHULL_CONVEXHULL_H

#include <vector>
#include <fstream>
#include <stack>
#include "Point.h"

using namespace std;

class ConvexHull {
private:
    vector<Point> pointList;    // List of Points, end up removing duplicated angles from
    vector<Point> allPts;
    vector<Point> intPts;       // Interior Points
    vector<Point> extPts;
    std::stack<Point> hullPoints;    // Hull Perimeter
public:
    ConvexHull();               // Default Constructor
    void findBottom();          // Find bottom-most point, store in first index hullPerim
    void sortAng();             // Sorts pointList by polar angle from bottom point
    void calcAng();             // Calculates polar angle from bottom-most point & horizontal axis (for all points)
    void checkDuplicateAng();   // Check for duplicate angles and throw out all duplicates except farthest
    bool pointOrient(const Point&, const Point&, const Point&);
    const Point beyondTop();
    void findIntPts();
    void writeHull();           // Write hull to file
    void writeInt();            // Write interior pts to file
};


#endif //CONVEXHULL_CONVEXHULL_H

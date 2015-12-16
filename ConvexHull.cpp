#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "ConvexHull.h"

ConvexHull::ConvexHull() {
    string line, value;
    double x,y;

    ifstream inFile;
    inFile.open("Data.txt");

    while (getline(inFile,line)) {
        stringstream linestream(line);
        int i = 0;
        while (getline(linestream, value, ',')) {
            if (i == 0)
                x = atof(value.c_str());
            if (i == 1)
                y = atof(value.c_str());
            i++;
        }
        Point* p = new Point(x,y);
        pointList.push_back(*p);
        delete p;
    }

    findBottom();           // Find the bottom-most point
    calcAng();              // Calculate angle of all points, based on bottom most point and horizontal axis
    sortAng();              // Sort pointList by angle, starting at element 2
    allPts = pointList;     // Copy points before removing duplicates
    checkDuplicateAng();    // Check for duplicate angles in set, throw all but 1 out

    if (pointList.size() < 3) {
        cout << "Not enough points for a convex hull, terminating..." << endl;
    }
    else {
        // Add first three points to stack
        for (int i = 0; i < 3; i++)
            hullPoints.push(pointList[i]);
        for (int i = 3; i < pointList.size(); i++) {
            while (!(pointOrient(beyondTop(),hullPoints.top(),pointList[i])))
                hullPoints.pop();
            hullPoints.push(pointList[i]);
        }

        writeHull();
        findIntPts();
        writeInt();
    }

}

void ConvexHull::findBottom() {
    int bottInd = 0;
    for (int i = 1; i < pointList.size(); i++) {
        if (pointList[i].getY() < pointList[bottInd].getY())
            bottInd = i;
        else if (pointList[i].getY() == pointList[bottInd].getY()) {
            if (pointList[i].getX() < pointList[bottInd].getX()) {
                bottInd = i;
            }
        }
    }
    // Swap bottom-most point with first index in pointList
    Point temp = pointList[bottInd];
    pointList[bottInd] = pointList[0];
    pointList[0] = temp;
    pointList[0].setAng(0);
}

void ConvexHull::calcAng() {
    double cosAngle, angle;
    Point bottPt = pointList[0];                        // Bottom most point
    Point horzPt((bottPt.getX()+1.0),bottPt.getY());      // Imaginary point to form horizontal axis

    double sideC = 1.0;                                 // Horizontal Side

    for (int i = 1; i < pointList.size(); i++) {
        double sideA = pointList[i].distTo(horzPt);
        double sideB = pointList[i].distTo(bottPt);

        cosAngle = (pow(sideA, 2) - pow(sideB, 2) - pow(sideC, 2)) / ((-1) * 2 * sideB * sideC);
        angle = (180/3.14159265)*acos(cosAngle);

        pointList[i].setAng(angle);
    }
}

void ConvexHull::sortAng() {
    bool swap = true;
    Point temp(0,0);
    while (swap) {
        swap = false;
        for (int i = 1; i < pointList.size() - 1; i++) {
            if (pointList[i].getAng() > pointList[i+1].getAng()) {
                temp = pointList[i];
                pointList[i] = pointList[i+1];
                pointList[i+1] = temp;
                swap = true;
            }
            else if (pointList[i].getAng() == pointList[i+1].getAng()) {
                double dist1 = pointList[0].distTo(pointList[i]);
                double dist2 = pointList[0].distTo(pointList[i+1]);
                if (dist1 > dist2) {
                    temp = pointList[i];
                    pointList[i] = pointList[i+1];
                    pointList[i+1] = temp;
                    swap = true;
                }
            }
        }
    }
}

void ConvexHull::checkDuplicateAng() {
    Point bottPt(pointList[0]);
    vector<Point>::iterator it = pointList.begin();
    it++;
    for (int i = 1; i < pointList.size() - 1; i++) {
        if (pointList[i].getAng() == pointList[i+1].getAng()) {
            if (pointList[i].distTo(bottPt) < pointList[i + 1].distTo(bottPt)) {
                it = pointList.erase(it);
            }
            else {
                it = pointList.erase(it + 1);
            }
        }
        it++;
    }
}

bool ConvexHull::pointOrient(const Point& pt1, const Point& pt2, const Point& pt3) {
    double crossProd = (pt2.getX()-pt1.getX())*(pt3.getY()-pt1.getY())-(pt2.getY()-pt1.getY())*(pt3.getX()-pt1.getX());
    if (crossProd > 0)
        return true;
    else
        return false;
}

const Point ConvexHull::beyondTop() {
    Point topPt(hullPoints.top());
    hullPoints.pop();
    Point underTop(hullPoints.top());
    hullPoints.push(topPt);
    return underTop;
}

void ConvexHull::writeHull() {
    int size = hullPoints.size();
    ofstream outFile;
    outFile.open("Hull.txt");
    for (int i = 0; i < size - 1; i++) {
        outFile << hullPoints.top().getX() << "," << hullPoints.top().getY() << endl;
        extPts.push_back(hullPoints.top());
        hullPoints.pop();
    }
    outFile << hullPoints.top().getX() << "," << hullPoints.top().getY();
    extPts.push_back(hullPoints.top());
    outFile.close();
}

void ConvexHull::writeInt() {
    int size = intPts.size();
    ofstream outFile;
    outFile.open("Interior.txt");
    for (int i = 0; i < size - 1; i++) {
        outFile << intPts[i].getX() << "," << intPts[i].getY() << endl;
    }
    outFile << intPts[size-1].getX() << "," << intPts[size-1].getY();
    outFile.close();
}

void ConvexHull::findIntPts() {
    for (int i = 0; i < allPts.size(); i++) {
        bool add = true;
        int j = 0;
        while (add && j != extPts.size()) {
            if (allPts[i] == extPts[j])
                add = false;
            else
                j++;
        }
        if (add) {
            intPts.push_back(allPts[i]);
        }
    }
}

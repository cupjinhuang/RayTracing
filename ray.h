#ifndef RAY_H
#define RAY_H
#include "point.h"
#define IDEPTH 5

class Ray
{
    Point origin;
    Vector direction;
    int iteration;
public:
    Ray(Point, Vector, int);
    Ray(const Ray&);

    Point* getOrigin() {return &origin;}
    Vector* getDirection() {return &direction;}

    int getIteration() {return iteration;}
    void setIteration(int i) {iteration = i;}
    bool isValid() {return iteration < IDEPTH && iteration >= 0;}

    Point* getPoint(float);
    Ray* reflectRay(float, Point*);
    Ray* refractRay(float, Point*, float);

    void print();

    ~Ray() {}
};

#endif // RAY_H

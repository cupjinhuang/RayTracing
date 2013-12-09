#ifndef POINT_H
#define POINT_H
#include "matrix.h"
/*
  Point class: abstract point in a 3D space
*/

#define THRE 0.2
#define ITHRE 0.001
#define RAYLENGTH 1e4
#define PRES 32768
#define VECTORX Vector(1, 0, 0)
#define VECTORY Vector(0, 1, 0)
#define VECTORZ Vector(0, 0, 1)

class Point;
typedef Point Vector;

class Matrix;

class Point
{
    float x;
    float y;
    float z;

public:
    Point(float, float, float);
    Point(const Point&);

    //getters
    inline float getX() {return x;}
    inline float getY() {return y;}
    inline float getZ() {return z;}

    //setters
    inline void setX(float X) {x = X;}
    inline void setY(float Y) {y = Y;}
    inline void setZ(float Z) {z = Z;}

    //operators
    friend Point operator*(Matrix, Point);
    friend Point operator*(float, Point);
    friend Point operator*(Point, float);
    friend Point operator/(Point, float);
    Point operator+(Point p)
    {
        return Point(x + p.x, y + p.y, z + p.z);
    }
    Point operator-(Point p)
    {
        return Point(x - p.x, y - p.y, z - p.z);
    }
    Point& operator=(Point p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }
    bool equal(Point p)
    {
        bool bx = (x - p.x <= THRE) && (p.x - x <= THRE);
        bool by = (y - p.y <= THRE) && (p.y - y <= THRE);
        bool bz = (z - p.z <= THRE) && (p.z - z <= THRE);
        return bx && by && bz;
    }
    bool operator !=(Point p)
    {
        return !(this->equal(p));
    }
    Point* normalize();

    //Point-only operations
    friend float distance(Point*, Point*);
    //Vector-only operations
    friend float innerProduct(Point*, Point*);
    friend Point* crossProduct(Point*, Point*);
    friend float length(Point*);
    friend float cosine(Point*, Point*);
    friend Point* projector(Point*, Point*);
    friend Point* reflection(Point*, Point*);
    friend Point* refraction(Point*, Point*, float);
    void print();
    ~Point() {}
};

float innerProduct(Point* p1, Point* p2);
Point* crossProduct(Point* p1, Point* p2);
float length(Point* p1);
float distance(Point* p1, Point* p2);
float cosine(Point* p1, Point* p2);
Point* projector(Point* p1, Point* p2);
Point* reflection(Point* p1, Point* p2);
Point* refraction(Point* p1, Point* p2, float index);

#endif // POINT_H

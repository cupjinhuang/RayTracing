#ifndef POLYGON_H
#define POLYGON_H
#include <QVector>
#include "point.h"
#include "ray.h"
#define ATHRE 0.01

class Point;
class Ray;

class Polygon
{
protected:
    Point origin;
    Vector xaxis;
    Vector yaxis;
    Vector norm;
    QVector<Point> points; // Be careful! Polygon DOES NOT delete those pointers; there MUST be somewhere they are deleted!

public:
    Polygon(Point, Vector, Vector, QVector<Point>);
    Polygon(const Polygon&);

    float intersection(Ray);
    virtual bool inside(Point*);

    virtual ~Polygon(){}
};

class Triangle: public Polygon
{
    Triangle(Point, Vector, Vector, QVector<Point>);
    Triangle(Point, Point, Point);
    Triangle(const Triangle&);

    virtual bool inside(Point *);

    virtual ~Triangle(){}
};

#endif // POLYGON_H

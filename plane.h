#ifndef PLANE_H
#define PLANE_H
#include "model.h"

class Plane : public Model
{
protected:
    Point origin;
    Vector xaxis;
    Vector yaxis;
    Vector norm;

public:
    Plane(Point, Vector, Vector, Scene*, Color, float, float, float, float, float, float);
    Plane(const Plane&);

    virtual Color getColor(Point* p) {return color;}
    virtual Vector* normal(Point*);
    virtual float intersection(Ray);

    Point getCoordinate(Point *);

    virtual ~Plane(){}
};

class Chessboard : public Plane
{
protected:
    float length;
    Color color1;
public:
    Chessboard(float, Color, Point, Vector, Vector, Scene*, Color, float, float, float, float, float, float);
    Chessboard(const Chessboard&);

    Color getColor(Point*);

    virtual ~Chessboard(){}
};

#endif // PLANE_H

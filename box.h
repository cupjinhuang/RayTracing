#ifndef BOX_H
#define BOX_H
#include "model.h"
#include "plane.h"
#include "polygon.h"

class Box : public Model
{
    Point origin;
    Point diagon;

public:
    Box(Point, Point, Scene*, Color, float, float, float, float, float, float);
    Box(const Box&);

    virtual Vector* normal(Point*) {return NULL;}
    virtual float intersection(Ray);

    virtual ~Box() {}
};

#endif // BOX_H

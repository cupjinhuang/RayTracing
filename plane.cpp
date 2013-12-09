#include "plane.h"
#include <QtCore/qmath.h>

Plane::Plane(Point o, Vector x, Vector y, Scene* s, Color c, float rl, float df, float pc, float pe, float rr, float id):
    Model(s, c, rl, df, pc, pe, rr, id),
    origin(o), xaxis(x), yaxis(y), norm(0, 0, 0)
{
    Point *n = crossProduct(&xaxis, &yaxis)->normalize();
    norm = *n;
    delete n;
}

Plane::Plane(const Plane & p):
    Model(p.scene, p.color, p.reflectCo, p.diffCo, p.phongCo, p.phongExp, p.refractCo, p.index),
    origin(p.origin), xaxis(p.xaxis), yaxis(p.yaxis), norm(0, 0, 0)
{
    Point *n = crossProduct(&xaxis, &yaxis)->normalize();
    norm = *n;
    delete n;
}

Vector* Plane::normal(Point *p)
{
    return new Vector(norm);
}

float Plane::intersection(Ray r)
{
    Point* p = new Point(origin - *(r.getOrigin()));
    float on = innerProduct(p, &norm);
    delete p;
    float bn = innerProduct(r.getDirection(), &norm);
    if((bn <= ITHRE) && (bn >= -ITHRE))
    {
        return 0;
    }
    else
    {
        float res = on / bn;
        //if((res >= RAYLENGTH) || (res <= -RAYLENGTH) || ((res <= THRE * 10) && (res >= -THRE * 10)))
        if(res >= RAYLENGTH || res <= THRE)
        {
            return 0;
        }
        else return res;
    }
}

Point Plane::getCoordinate(Point* p)
{
    Vector v = *p - origin;
    return v / Matrix(xaxis, yaxis, norm);
}

Chessboard::Chessboard(float w, Color c1, Point o, Vector x, Vector y, Scene *s, Color c, float rl, float df, float pc, float pe, float rr, float id):
    Plane(o, x, y, s, c, rl, df, pc, pe, rr, id),
    length(w), color1(c1)
{
}

Chessboard::Chessboard(const Chessboard & c):
    Plane(c.origin, c.xaxis, c.yaxis, c.scene, c.color, c.reflectCo, c.diffCo, c.phongCo, c.phongExp, c.refractCo, c.index),
    length(c.length), color1(c.color1)
{
}

Color Chessboard::getColor(Point *p)
{
    Point p1 = getCoordinate(p);
    int x1 = qFloor(p1.getX() / length);
    int x2 = qFloor(p1.getY() / length);
    if(((x1 ^ x2) & 1) == 1)
    {
        return color1;
    }
    else
    {
        return color;
    }
}

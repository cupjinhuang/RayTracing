#include "polygon.h"
#include <QtCore/qmath.h>

Polygon::Polygon(Point o, Vector x, Vector y, QVector<Point *> p):
    origin(o), xaxis(x), yaxis(y), points(p), norm(0, 0, 0)
{
    norm = *(crossProduct(&xaxis, &yaxis)->normalize());
}

Polygon::Polygon(const Polygon& p):
    origin(p.origin), xaxis(p.xaxis), yaxis(p.yaxis), points(p.points), norm(0, 0, 0)
{
    norm = *(crossProduct(&xaxis, &yaxis)->normalize());
}

float Polygon::intersection(Ray r)
{
    Point* op = new Point(origin - *(r.getOrigin()));
    float on = innerProduct(op, &norm);
    delete op;
    float bn = innerProduct(r.getDirection(), &norm);
    if((bn <= ITHRE) && (bn >= -ITHRE))
    {
        return 0;
    }
    else
    {
        float res = on / bn;
        if((res >= RAYLENGTH) || (res <= THRE * 10))
        {
            return 0;
        }
        else
        {
            Point* inter = r.getPoint(res);
            if(inside(inter)) return res;
            else return 0;
        }
    }
}

bool Polygon::inside(Point* p)
{
    Point pc = *p / Matrix(xaxis, yaxis, norm);
    pc.setZ(0);

    float angle = 0;
    int s = points.size();
    if(s < 3) return true;
    Point *p1;
    Point *p2;
    for(int i = 0; i < s; i ++)
    {
        p1 = points.at(i);
        if(i == 0)
        {
            p2 = points.at(s - 1);
        }
        Point p3 = *p1 - *p;
        Point p4 = *p2 - *p;
        if(cosine(&p3, &p4) <= ATHRE - 1) return true;
        angle += qAsin(crossProduct(&p3, &p4)->getZ());
        p2 = p1;
    }
    return !((angle <= ATHRE) && (angle >= -ATHRE));
}

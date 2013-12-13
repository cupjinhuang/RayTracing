#include "polygon.h"
#include <QtCore/qmath.h>

Polygon::Polygon(Point o, Vector x, Vector y, QVector<Point> p):
    origin(o), xaxis(x), yaxis(y), norm(0, 0, 0), points(p)
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
    if(op != NULL)
    {
        delete op;
        op = NULL;
    }
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
        Point p3 = p1 - p;
        Point p4 = p2 - p;
        if(cosine(&p3, &p4) <= ATHRE - 1) return true;
        angle += qAsin(crossProduct(&p3, &p4)->getZ());
        p2 = p1;
    }
    return !((angle <= ATHRE) && (angle >= -ATHRE));
}

Triangle::Triangle(Point p,Vector v1,Vector v2,QVector<Point> q):
    Polygon(p, v1, v2, q)
{
}

Triangle::Triangle(Point p1, Point p2, Point p3):
    Polygon(p1, p2 - p1, p3 - p1, QVector<Point>())
{
    points.append(p1);
    points.append(p2);
    points.append(p3);
}

Triangle::Triangle(const Triangle& t):
    Polygon(t.origin, t.xaxis, t.yaxis, t.points)
{
}


bool Polygon::inside(Point* p)
{
    Point pc = *p / Matrix(xaxis, yaxis, norm);
    pc.setZ(0);
    if((pc.getX() >= 0)&&(pc.getX() <= 1))
    {
        if((pc.getY() >= 0) && (pc.getY() <= 1))
        {
            if(pc.getX() + pc.getY() <= 1)
            {
                return true;
            }
        }
    }
    return false;
}

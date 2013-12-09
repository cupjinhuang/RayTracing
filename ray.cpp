#include "ray.h"
#include <QDebug>

Ray::Ray(Point p, Vector v, int it = 0) : origin(p), direction(*v.normalize()), iteration(it)
{
}

Ray::Ray(const Ray& r): origin(r.origin), direction(r.direction), iteration(r.iteration)
{
}

Point *Ray::getPoint(float t)
{
    return new Point(origin + t * direction);
}

Ray* Ray::reflectRay(float t, Point* n)
{
    Point* p = getPoint(t);
    Point* r = reflection(&direction, n);
    Ray* res = new Ray(*p, *r, iteration + 1);
    delete p;
    delete r;
    return res;
}

Ray* Ray::refractRay(float t, Point* n, float index)
{
    Point* p = getPoint(t);
    Point* rfr = refraction(&direction, n, index);
    float ip = innerProduct(n, rfr);
    Ray *res;
    if(ip == 1 || ip == -1)
    {
        res = new Ray(*p, *rfr, -1);
    }
    else if(ip <= THRE && ip >= -THRE)
    {
        res = new Ray(*p, direction,iteration + 1);
    }
    else
    {
        res = new Ray(*p, *rfr, iteration + 1);
    }
    delete p;
    delete rfr;
    return res;
}

void Ray::print()
{
    qDebug() << "Ray:" << "origin";
    origin.print();
    qDebug() << "direction";
    direction.print();
}

#include "point.h"
#include <QDebug>
#include <QtCore/qmath.h>

Point::Point(float X = 0, float Y = 0, float Z = 0) : x(X), y(Y), z(Z)
{
}

Point::Point(const Point &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

Point operator*(float s, Point p)
{
    return Point(s * p.getX(), s * p.getY(), s * p.getZ());
}

Point operator*(Point p, float s)
{
    return Point(s * p.getX(), s * p.getY(), s * p.getZ());
}

Point operator/(Point p, float s)
{
    return Point(p.getX() / s, p.getY() / s, p.getZ() / s);
}

float innerProduct(Point* p1, Point* p2)
{
    return p1->x * p2->x + p1->y * p2->y + p1->z * p2->z;
}

Point* crossProduct(Point* p1, Point* p2) // the whole basis is left-handed
{
    return new Point(p1->z * p2->y - p1->y * p2->z , p2->z * p1->x - p1->z * p2->x, p2->x * p1->y - p1->x * p2->y);
}

float length(Point* p1)
{
    return qSqrt(p1->x * p1->x + p1->y * p1->y + p1->z * p1->z);
}

float distance(Point* p1, Point* p2)
{
    Vector d = *p1 - *p2;
    return qSqrt(d.x * d.x + d.y * d.y + d.z * d.z);
}

Point *Point::normalize()
{
    float f = qSqrt(x * x + y * y + z * z);
    x /= f;
    y /= f;
    z /= f;
    return this;
}

float cosine(Point* p1, Point* p2)
{
    p1->normalize();
    p2->normalize();
    float res = innerProduct(p1, p2);
    return res;
}

Point* projector(Point* p1, Point* p2)
{
    return new Point(*p2 * cosine(p1, p2));
}

Point* reflection(Point* p1, Point* p2)
{
    Point* proj = projector(p1, p2);
    Point pr2 = -2 * *proj;
    delete proj;
    return new Point(pr2 + *p1);
}

Point* refraction(Point* p1, Point* p2, float index)
{

    Point*proj = projector(p1, p2);
    Point para = (*p1 - *proj);
    para = para * index;
    float sine = length(&para);
    if(sine >=1)
    {
        //qDebug() << sine;
        return p2;
    }
    else
    {
        //qDebug() << "succ" << sine;
        proj->normalize();
        Point* res = new Point(para + qSqrt(1 - sine * sine) * *proj);
        delete proj;
        return res;
    }
}

void Point::print()
{
    qDebug() << "Point:";
    qDebug() << x << y << z;
}

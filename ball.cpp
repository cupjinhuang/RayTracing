#include "ball.h"
#include "point.h"
#include <QtCore/qmath.h>
#include <QDebug>

Ball::Ball(float r, Point c, Scene* s, Color i, float rl, float df, float pc, float pe, float rr, float ind):
    Model(s, i, rl, df, pc, pe, rr, ind),
    radius(r), center(c)
{
}

Ball::Ball(const Ball &b):
    Model(b.scene, b.color, b.reflectCo, b.diffCo, b.phongCo, b.phongExp, b.refractCo, b.index),
    radius(b.radius), center(b.center)
{
}

float Ball::intersection(Ray r)
{
    Point* o = r.getOrigin();
    float dist = distance(o, &center);
    Point co = center - *o;
    Point* d = r.getDirection();
    float close = innerProduct(&co, d);
    if(close < 0) return 0;

    float sq = (radius * radius) - (dist * dist) + (close * close);
    if(sq <= THRE) return 0;
    else
    {
        float l = qSqrt(sq);
        if(dist <= radius + THRE)
        {
            //qDebug() << close + l;
            return close + l;
        }
        else
        {
            //qDebug() << close - l;
            return close - l;
        }
    }
}

Vector* Ball::normal(Point *p)
{
    Point* pc = new Point(*p - center);
    pc->normalize();
    return pc;
}


void Ball::print()
{
    qDebug() << "Ball:";
    qDebug() << "radius" << radius;
    qDebug() << "center";
    center.print();
}

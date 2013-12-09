#include "box.h"

Box::Box(Point o, Point d, Scene *s, Color c, float rl, float df, float pc, float pe, float rr, float id):
    Model(s, c, rl, df, pc, pe, rr, id),
    origin(qMin(o.getX(), d.getX()), qMin(o.getY(), d.getY()), qMin(o.getZ(), d.getZ())),
    diagon(qMax(o.getX(), d.getX()), qMax(o.getY(), d.getY()), qMax(o.getZ(), d.getZ()))
{
}

Box::Box(const Box & b):
    Model(b.scene, b.color, b.reflectCo, b.diffCo, b.phongCo, b.phongExp, b.refractCo, b.index),
    origin(b.origin), diagon(b.diagon)
{
}

float Box::intersection(Ray r)
{
    float z0 = Polygon(origin, VECTORX, VECTORY, QVector<Point *>()).intersection(r);
    float y0 = Polygon(origin, VECTORX, VECTORZ, QVector<Point *>()).intersection(r);
    float x0 = Polygon(origin, VECTORZ, VECTORY, QVector<Point *>()).intersection(r);

    float z1 = Polygon(diagon, VECTORX, VECTORY, QVector<Point *>()).intersection(r);
    float y1 = Polygon(diagon, VECTORX, VECTORZ, QVector<Point *>()).intersection(r);
    float x1 = Polygon(diagon, VECTORY, VECTORY, QVector<Point *>()).intersection(r);

    float tMin = qMax(qMax(qMin(x0, x1), qMin(y0, y1)), qMin(z0, z1));
    float tMax = qMin(qMin(qMax(x0, x1), qMax(y0, y1)), qMax(z0, z1));
    if(tMax - tMin <= THRE * 10) return 0;
    return 0;
}

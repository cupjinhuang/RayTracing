#include "source.h"
#include <QtCore/qmath.h>
#include <QTime>
#define PI 3.1415926

Source::Source(Point p, Intensity i, float v): origin(p), intensity(i), variance(v)
{
}

Source::Source(const Source &s):origin(s.origin), intensity(s.intensity), variance(s.variance)
{
}

QVector<Point *> Source::sampleOrigin()
{
    QVector<Point*> sources;
    for(int i = 0; i < SAMPLERATE; i ++)
    {
        float r = (qrand() % PRES) * (variance / (PRES + 0.0));
        float theta = (qrand() % PRES) * ((2 * PI) / PRES);
        float phi = (qrand() % PRES) * (PI / PRES);
        float xOffSet = r * qCos(theta) * qSin(phi);
        float yOffSet = r * qSin(theta) * qSin(phi);
        float zOffSet = r * qCos(phi);
        Point* p;
        p = new Point(origin.getX() + xOffSet, origin.getY() + yOffSet, origin.getZ() + zOffSet);
        sources.append(p);
    }
    return sources;
}

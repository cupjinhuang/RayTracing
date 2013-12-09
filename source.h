#ifndef SOURCE_H
#define SOURCE_H
#include "point.h"
#include "intensity.h"
#include <QVector>

#define SAMPLERATE 1

class Source
{
    Point origin;
    Intensity intensity;
    float variance;
public:
    Source(Point, Intensity, float);
    Source(const Source &);

    Point* getOrigin() {return &origin;}
    QVector<Point*> sampleOrigin();

    Intensity getIntensity() {return intensity;}
    Intensity getIntensity(float f) {return 1000 * intensity * (1 / (f * f));}
    void setIntensity(Intensity i) {intensity = i;}

    ~Source()
    {
    }
};

#endif // SOURCE_H

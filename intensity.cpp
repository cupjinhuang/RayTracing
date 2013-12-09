#include "intensity.h"
#include <QtCore/qmath.h>
#include <QDebug>

Intensity::Intensity(float R, float G, float B): r(R), g(G), b(B)
{
}

Intensity::Intensity(float C): r(C), g(C), b(C)
{
}

Intensity::Intensity(const Intensity &i): r(i.r), g(i.g), b(i.b)
{
}

Intensity operator*(Intensity i, float coef)
{
    return Intensity(i.r * coef, i.g * coef, i.b * coef);
}

Intensity operator*(float coef, Intensity i)
{
    return Intensity(i.r * coef, i.g * coef, i.b * coef);
}


float logistic(float a)
{
    float x = LOGCO * a - OFFSET;
    if(x > 10) return 1;
    x = qExp(x);
    float coef = x / (1 + x);
    return coef;
}

QRgb Intensity::toRGB()
{
    float coefR = 255 * logistic(r);
    float coefG = 255 * logistic(g);
    float coefB = 255 * logistic(b);
    return qRgb(int(coefR), int(coefG), int(coefB));
}

Intensity Intensity::filter(Color c)
{
    return Intensity((r + ENLIGHTEN) * (c.getR() + 10) / 256.0, (g + ENLIGHTEN) * (c.getG() + 10) / 256.0, (b + ENLIGHTEN) * (c.getB() + 10) / 256.0);
}

void Intensity::print()
{
    qDebug() << "Intensity";
    qDebug() << r << g << b;
}

#ifndef INTENSITY_H
#define INTENSITY_H
#include <QColor>
#include "color.h"

#define LOGCO 2
#define OFFSET 1
#define ENLIGHTEN 0

class Color;

class Intensity
{
    float r;
    float g;
    float b;
public:
    Intensity(float, float, float);
    Intensity(float);
    Intensity(const Intensity&);

    float getR() {return r;}
    float getG() {return g;}
    float getB() {return b;}

    void setR(float R) {r = R;}
    void setG(float G) {g = G;}
    void setB(float B) {b = B;}

    Intensity operator+(Intensity i)
    {
        return Intensity(r + i.r, g + i.g, b + i.b);
    }
    Intensity operator-(Intensity i)
    {
        return Intensity(r - i.r, g - i.g, b - i.b);
    }
    friend Intensity operator*(Intensity, float);
    friend Intensity operator*(float, Intensity);
    Intensity operator=(Intensity i)
    {
        r = i.r;
        g = i.g;
        b = i.b;
        return *this;
    }
    Intensity filter(Color c);

    void print();
    QRgb toRGB();

    ~Intensity(){}
};

#endif // INTENSITY_H

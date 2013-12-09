#ifndef COLOR_H
#define COLOR_H
#include "intensity.h"

class Intensity;
class Color
{
    int r;
    int g;
    int b;
public:
    Color(int, int, int);
    Color(int);
    Color(const Color&);

    int getR() {return r;}
    int getG() {return g;}
    int getB() {return b;}

    void setR(int R) {r = R;}
    void setG(int G) {g = G;}
    void setB(int B) {b = B;}

    ~Color(){}
};

#endif // COLOR_H

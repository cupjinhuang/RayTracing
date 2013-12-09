#include "color.h"
#include <QtCore/qmath.h>

Color::Color(int R, int G, int B): r(R), g(G), b(B)
{
}

Color::Color(int C): r(C), g(C), b(C)
{
}

Color::Color(const Color &c): r(c.r), g(c.g), b(c.b)
{
}

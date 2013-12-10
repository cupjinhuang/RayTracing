#include "baseComponents.h"
#include <QtCore/qmath.h>
float3 operator*(float3 p, matrix m)
{
    float3 calc;
    calc.x = p.x * m.x[0] + p.y * m.y[0] + p.z * m.z[0];
    calc.y = p.x * m.x[1] + p.y * m.y[1] + p.z * m.z[1];
    calc.z = p.x * m.x[2] + p.y * m.y[2] + p.z * m.z[2];
    return calc;
}
float3 operator*(matrix m, float3 p)
{
    float3 calc;
    calc.x = p.x * m.x[0] + p.y * m.y[0] + p.z * m.z[0];
    calc.y = p.x * m.x[1] + p.y * m.y[1] + p.z * m.z[1];
    calc.z = p.x * m.x[2] + p.y * m.y[2] + p.z * m.z[2];
    return calc;
}
float inner(float3 f1, float3 f2)
{
    return f1.x*f2.x+f1.y*f2.y+f1.z*f2.z;
}
float norm(float3 f)
{
    return qSqrt(inner(f, f));
}
float distance(float3 f1, float3 f2)
{
    return norm(f1- f2);
}
float vecCos(float3 f1, float3 f2)
{
    return inner(f1, f2) / (norm(f1) * norm(f2));
}

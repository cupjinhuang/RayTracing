#include "matrix.h"
#include <QtCore/qmath.h>
#include <QDebug>

Matrix::Matrix()
{
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            entries[i][j] = (i == j);
        }
    }
}

Matrix::Matrix(Vector e1, Vector e2, Vector e3)
{
    entries[0][0] = e1.getX();
    entries[1][0] = e1.getY();
    entries[2][0] = e1.getZ();
    entries[0][1] = e2.getX();
    entries[1][1] = e2.getY();
    entries[2][1] = e2.getZ();
    entries[0][2] = e3.getX();
    entries[1][2] = e3.getY();
    entries[2][2] = e3.getZ();
}

Matrix::Matrix(const Matrix & m)
{
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            entries[i][j] = m.entries[i][j];
        }
    }
}

Point operator*(Matrix m, Point p)
{
    float f[3];
    f[0] = p.x * m.entries[0][0] + p.y * m.entries[0][1] + p.z * m.entries[0][2];
    f[1] = p.x * m.entries[1][0] + p.y * m.entries[1][1] + p.z * m.entries[1][2];
    f[2] = p.x * m.entries[2][0] + p.y * m.entries[2][1] + p.z * m.entries[2][2];
    return Point(f[0], f[1], f[2]);
}

Point operator/(Point p, Matrix m)
{
    return m.inverse() * p;
}

Matrix operator*(Matrix m, float scale)
{
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            m.entries[i][j] *= scale;
        }
    }
    return m;
}

Matrix operator*(float scale, Matrix m)
{
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            m.entries[i][j] *= scale;
        }
    }
    return m;
}

Matrix operator*(Matrix m1, Matrix m2)
{
    Matrix m;
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            m.entries[i][j] = 0;
            for(int k = 0; k < 3; k ++)
            {
                m.entries[i][j] += m1.entries[i][k] * m2.entries[k][j];
            }
        }
    }
    return m;
}

void Matrix::rotateX(float t)
{
    Vector v1(1, 0, 0);
    Vector v2(0, qCos(t), qSin(t));
    Vector v3(0, -qSin(t), qCos(t));
    *this = Matrix(*this * Matrix(v1, v2, v3) );
}

void Matrix::rotateY(float t)
{
    Vector v1(qCos(t), 0, -qSin(t));
    Vector v2(0, 1, 0);
    Vector v3(qSin(t), 0, qCos(t));
    *this = Matrix(*this * Matrix(v1, v2, v3));
}

void Matrix::rotateZ(float t)
{
    Vector v1(qCos(t), qSin(t), 0);
    Vector v2(-qSin(t), qCos(t), 0);
    Vector v3(0, 0, 1);
    *this = Matrix( *this * Matrix(v1, v2, v3));
}

void Matrix::print()
{
    qDebug() << "Matrix";
    for(int i = 0; i < 3; i ++)
    {
        qDebug() << entries[i][0] << entries[i][1] << entries[i][2];
    }
}

Point Matrix::getX()
{
    return Point(entries[0][0], entries[1][0], entries[2][0]);
}

Point Matrix::getY()
{
    return Point(entries[0][1], entries[1][1], entries[2][1]);
}

Point Matrix::getZ()
{
    return Point(entries[0][2], entries[1][2], entries[2][2]);
}

float Matrix::determinant()
{
    float f1 = entries[0][0] * (entries[1][1] * entries[2][2] - entries[1][2] * entries[2][1]);
    float f2 = entries[0][1] * (entries[1][0] * entries[2][2] - entries[1][2] * entries[2][0]);
    float f3 = entries[0][2] * (entries[1][0] * entries[2][1] - entries[1][1] * entries[2][0]);
    return f1 - f2 + f3;
}

Matrix Matrix::inverse()
{
    float f00 = entries[1][1] * entries[2][2] - entries[2][1] * entries[1][2];
    float f01 = -(entries[0][1] * entries[2][2] - entries[0][2] * entries[2][1]);
    float f02 = entries[0][1] * entries[1][2] - entries[0][2] * entries[1][1];
    float f10 = -(entries[1][0] * entries[2][2] - entries[2][0] * entries[1][2]);
    float f11 = entries[0][0] * entries[2][2] - entries[2][0] * entries[0][2];
    float f12 = -(entries[0][0] * entries[1][2] - entries[0][2] * entries[1][0]);
    float f20 = entries[1][0] * entries[2][1] - entries[2][0] * entries[1][1];
    float f21 = -(entries[0][0] * entries[2][1] - entries[0][1] * entries[2][0]);
    float f22 = entries[0][0] * entries[1][1] - entries[0][1] * entries[1][0];

    return (1 / determinant()) * Matrix(Vector(f00, f01, f02), Vector(f10, f11, f12), Vector(f20, f21, f22));
}

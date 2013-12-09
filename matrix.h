#ifndef MATRIX_H
#define MATRIX_H
#include "point.h"
class Point;
typedef Point Vector;

class Matrix
{
    float entries[3][3];

public:
    Matrix();
    Matrix(Vector, Vector, Vector);
    Matrix(const Matrix&);

    //operations
    friend Point operator*(Matrix, Point);
    friend Point operator/(Point, Matrix);
    friend Matrix operator*(float, Matrix);
    friend Matrix operator*(Matrix, float);
    friend Matrix operator*(Matrix, Matrix);
    Matrix operator=(Matrix m)
    {
        for(int i = 0; i < 3; i ++)
        {
            for(int j = 0; j < 3; j ++)
            {
                entries[i][j] = m.entries[i][j];
            }
        }
        return *this;
    }

    void rotateX(float);
    void rotateY(float);
    void rotateZ(float);

    Point getX();
    Point getY();
    Point getZ();

    Matrix inverse();
    float determinant();
    void print();

    ~Matrix() {}
};

#endif // MATRIX_H

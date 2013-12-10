#ifndef CAMERA_H
#define CAMERA_H
#include "point.h"
#include "matrix.h"
#include "ray.h"
#define CHEIGHT 600
#define CWIDTH 800
#define CDEPTH 500

#define DIVH 1
#define DIVW 1

class Camera
{    
    Point origin;
    Matrix basis;
public:

    Camera(Point);
    Camera(Point, Point, Point, Point);

    Point getOrigin() {return origin;}
    void setOrigin(Point o) {origin = o;}

    void rotateX(float);
    void rotateY(float);
    void rotateZ(float);

    void print();

    QVector<Ray*> pixelLight(int coorX, int coorY);

    ~Camera(){}
};

#endif // CAMERA_H

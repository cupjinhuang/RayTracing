#ifndef BALL_H
#define BALL_H
#include "model.h"

class Ball : public Model
{
    float radius;
    Point center;
public:
    Ball(float, Point, Scene*, Color, float, float, float, float, float, float);
    Ball(const Ball&);

    Vector* normal(Point*);
    float intersection(Ray);
    void print();

    virtual ~Ball(){}
};

#endif // BALL_H

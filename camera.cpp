#include <QTime>
#include <QDebug>
#include "camera.h"

Camera::Camera(Point ORIGIN) : origin(ORIGIN), basis()
{
}

Camera::Camera(Point ORIGIN, Point OX, Point OY, Point OZ): origin(ORIGIN), basis(OX, OY, OZ)
{
}

QVector<Ray*> Camera::pixelLight(int coorX, int coorY)
{
    QTime t;
    t = QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    QVector<Ray*> result;
    for(int i = 0; i < DIVH; i ++)
    {
        for(int j = 0; j < DIVW; j ++)
        {
            float hOffSet = (i + (qrand() % PRES) / (PRES + 0.0)) / (DIVH + 0.0);
            float wOffSet = (j + (qrand() % PRES) / (PRES + 0.0)) / (DIVW + 0.0);
            Vector to(coorX + hOffSet, coorY + wOffSet, CDEPTH);
            Ray* toLight = new Ray(origin, basis * to, 0);
            result.append(toLight);
        }
    }
    return result;
}

void Camera::rotateX(float t)
{
    basis.rotateX(t);
}

void Camera::rotateY(float t)
{
    basis.rotateY(t);
}

void Camera::rotateZ(float t)
{
    basis.rotateZ(t);
}

void Camera::print()
{
    qDebug() << "Camera:";
    qDebug() << "origin";
    origin.print();
    qDebug() << "basis";
    basis.print();

}

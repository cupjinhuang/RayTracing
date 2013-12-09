#include "scene.h"
#include "ball.h"
#include "plane.h"
#include <QDebug>
#include <QTime>
#include <QPen>
#include <QLabel>
#include <QtCore/qmath.h>


Scene::Scene(QObject *parent):
    QGraphicsScene(parent),
    ambient(AMBIENT)
{
    setSceneRect(0, 0, CWIDTH, CHEIGHT);
    image = new QImage(CWIDTH, CHEIGHT, QImage::Format_RGB32);
    initialize();
}

void Scene::render()
{
    for(int i = -CWIDTH / 2; i < CWIDTH / 2; i ++)
    {
        for(int j = -CHEIGHT / 2; j < CHEIGHT / 2; j ++)
        {
            QVector<Ray*> rSeq = camera->pixelLight(i, j);
            int s = rSeq.size();
            Intensity rgb(0, 0, 0);
            while(!rSeq.empty())
            {
                Ray* tmp = rSeq.first();

                rgb = rgb + (1.0 / s) * getIntensity(tmp);
                rSeq.pop_front();
                delete tmp;
                tmp = 0;
            }
            image->setPixel(i + CWIDTH / 2, j + CHEIGHT / 2, rgb.toRGB());

        }

    }
}

int Scene::intersection(Ray r, float& fMin)
{
    int i = -1;
    fMin = 0;
    int s = models.size();
    for(int j = 0; j < s; j ++)
    {
        float f = models.at(j)->intersection(r);
        if(f > 0 && (f < fMin || fMin == 0))
        {
            fMin = f;
            i = j;
        }
    }
    return i;
}

Intensity Scene::getIntensity(Ray* r)
{
    if(!r->isValid()) return ambient;
    float fMin;
    int i = intersection(*r, fMin);
    if(i < 0)
    {
        return ambient;
    }
    else
    {
        Intensity it = models.at(i)->render(*r);
        return it;
    }
}

void Scene::initialize()
{
    Source* s1 = new Source(Point(SWIDTH, -SHEIGHT, -SDEPTH), Intensity(500000), 1000.0);
    Source* s2 = new Source(Point(SWIDTH * 0.5, -SHEIGHT * 1.1, -SDEPTH * 0.6), Intensity(10000, 20000, 60000), 50);
    Source* s3 = new Source(Point(-SWIDTH * 0.5, 0, -SDEPTH * 0.3), Intensity(20000, 4000, 2000), 50);
    sources.append(s1);
    sources.append(s2);
    sources.append(s3);
    camera = new Camera(Point(SWIDTH * 0.5, SHEIGHT * 0.5, -SDEPTH * 0.3 - CDEPTH));
    //camera->rotateX(0.0);
}

void Scene::sceneMain()
{
    qDebug() << "now in sceneMain";
    Chessboard* floor = new Chessboard(200, Color(255, 0, 0),
                                    Point(0, SHEIGHT * 0.8, 0),
                                    Vector(-1, 0, 0), Vector(0, 0, 1),
                                    this,
                                    Color(0, 255, 0),
                                    0.0, 0.7, 0.05, 20, 0, 1);
    Chessboard* background = new Chessboard(200, Color(255, 255, 0),
                                  Point(0, 0, SDEPTH * 1.5),
                                  Vector(1, 0, 0), Vector(0, 1, 0),
                                  this,
                                  Color(128, 128, 255),
                                  0.0, 0.7, 0.05, 20, 0, 1);
    models.append(floor);
    models.append(background);
    Plane* mirror = new Plane(Point(0.2 * SWIDTH, 0, 0),
                              Vector(0.2, 0, 1), Vector(0, -1, 0),
                              this,
                              Color(255, 255, 255),
                              1, 0, 0, 0, 0, 0);
    models.append(mirror);
    Ball* b2 = new Ball(200,
                        Point(2 * SWIDTH / 3,  2 * SHEIGHT / 3, SDEPTH / 3),
                        this,
                        Color(255, 224, 0),
                        0.95, 0.01, 0.01, 50, 0, 1.5);
    Ball* b3 = new Ball(300,
                        Point(SWIDTH / 2,  SHEIGHT / 2, SDEPTH * 0.3),
                        this,
                        Color(128, 128, 128),
                        0, 0, 0.1, 50, 0.9, 1.1);
    models.append(b2);
    models.append(b3);
    for(int i = 12; i < 13; i ++)
    {
        qDebug() << "Now rendering " << i;
        Ball* b1 = new Ball(200,
                            Point(SWIDTH * 0.55, SHEIGHT * 0.45, SDEPTH * (i / 20.0) ),
                            this, Color(255, 255, 255),
                            0.4, 0.2, 0.2, 50, 0, 1.5);
        //models.append(b1);
        QTime time;
        time.start();
        render();
        int diff = time.elapsed();
        qDebug() << "Render finished in" << diff / 1000.0 << "seconds.";

        QPixmap pixmap = QPixmap::fromImage(*image);
        QString str = "Ball_" + QString::number(i) + ".png";
        pixmap.save(str);
        addPixmap(pixmap);
        models.pop_back();
        delete b1;
        b1 = 0;
    }
    qDebug() << "Finished!";
}

float Scene::getSourceRay(int i, Point* p)
{
    int cnt = 0;
    QVector<Point *> org = sources.at(i)->sampleOrigin();
    int size = org.size();
    for(int j = 0; j < size; j ++)
    {
        Point* oi = org.at(j);
        Point* op = new Point(*p - *oi);
        Ray sourceRay(*oi, *op, 0);
        delete op;
        float f = distance(oi, p);
        int s = models.size();
        int k = 0;
        for(k = 0; k < s; k ++)
        {
            float s = models.at(k)->intersection(sourceRay);
            if((s > THRE * 10) && (f - s > THRE * 10)) break;
        }
        if(k == s && j == 0)
        {
            while(!org.empty())
            {
                Point* first = org.first();
                org.pop_front();
                delete first;
            }
            return 1;
        }
        else
        {
            if(k == s) cnt ++;
        }
    }
    while(!org.empty())
    {
        Point* first = org.first();
        org.pop_front();
        delete first;
    }
    return cnt / (size + 0.0);
}

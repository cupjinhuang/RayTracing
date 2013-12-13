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
    pixels = new QRgb*[800];
    for(int i = 0; i < 800; i ++)
    {
        pixels[i] = new QRgb[600];
    }
    initialize();
}

void Scene::render()
{
    for(int i = -CWIDTH / 2; i < CWIDTH / 2; i ++)
    {
        qDebug() << i;
        for(int j = -CHEIGHT / 2; j < CHEIGHT / 2; j ++)
        {
            QVector<Ray*> rSeq = camera->pixelLight(i, j);
            int s = rSeq.size();
            Intensity rgb(0, 0, 0);
            while(!rSeq.empty())
            {
                Ray* tmp = rSeq.front();

                rgb = rgb + (1.0 / s) * getIntensity(tmp);
                rSeq.pop_front();
                if(tmp != NULL)
                {
                    delete tmp;
                    tmp = NULL;
                }
            }
            pixels[i + CWIDTH / 2][j + CHEIGHT / 2] = rgb.toRGB();

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
    Source* s1 = new Source(Point(SWIDTH / 2, SHEIGHT / 2, SDEPTH / 2), Intensity(5000), 10.0);
    Source* s2 = new Source(Point(SWIDTH * 0.5, -SHEIGHT * 1.1, -SDEPTH * 0.6), Intensity(10000, 20000, 60000), 50);
    Source* s3 = new Source(Point(-SWIDTH * 0.5, 0, -SDEPTH * 0.3), Intensity(20000, 4000, 2000), 50);
    sources.append(s1);
    //sources.append(s2);
    //sources.append(s3);
    camera = new Camera(Point(SWIDTH * 0.5, SHEIGHT * 0.5, -SDEPTH * 0.3 - CDEPTH));
    camera->rotateZ(-0.1);
}

void Scene::sceneMain()
{
    qDebug() << "now in sceneMain";
    Chessboard* floor = new Chessboard(200, Color(255, 0, 0),
                                    Point(0, SHEIGHT, 0),
                                    Vector(-1, 0, 0), Vector(0, 0, 1),
                                    this,
                                    Color(0, 255, 0),
                                    0.0, 0.7, 0.05, 20, 0, 1);
    Chessboard* background = new Chessboard(200, Color(255, 255, 0),
                                  Point(0, 0, SDEPTH),
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
    //models.append(mirror);
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
    //models.append(b2);
    //models.append(b3);
    for(int i = 12; i < 13; i ++)
    {
        Ball* b1 = new Ball(200,
                            Point(SWIDTH * 0.55, SHEIGHT * 0.45, SDEPTH * (i / 20.0) ),
                            this, Color(255, 255, 255),
                            0.4, 0.2, 0.2, 50, 0, 1.5);
        //models.append(b1);
        for(int j = 0; j <10 ; j ++)
        {
            for(int k = 0; k < 10; k ++)
            {
                for(int l = 0; l < 10; l ++)
                {
                    Ball *b = new Ball(100, Point(SWIDTH * 0.1 * (j + 0.5), SHEIGHT * 0.1 * (k + 0.5), SDEPTH * 0.1 * (l + 0.5)),
                                       this, Color(255 * 0.1 * (j + 0.5), 255 * 0.1 * (k + 0.5), 255 * 0.1 * (l + 0.5)),
                        0, 0, 0.1, 50, 0.9, 1.1);
                    models.append(b);
                }
            }
        }
        QTime time;
        time.start();
        qDebug() << "Now rendering " << i;
        render();
        int diff = time.elapsed();
        qDebug() << "Render finished in" << diff / 1000.0 << "seconds.";

        QPixmap pixmap = QPixmap::fromImage(*image);
        QString str = "Ball_" + QString::number(i) + ".png";
        pixmap.save(str);
        addPixmap(pixmap);
        models.pop_back();
        if(b1 != NULL)
        {
            delete b1;
            b1 = NULL;
        }
    }
    qDebug() << "Finished!";
}

float Scene::getSourceRay(int i, Point* p)
{
    Point* oi1 = sources.at(i)->getOrigin();
    Ray sourceRay(*oi1, *p - *oi1, 0);
    float f1 = distance(oi1, p);
    int s1 = models.size();
    int k1 = 0;
    for(k1 = 0; k1 < s1; k1 ++)
    {
        float s = models.at(k1)->intersection(sourceRay);
        if((s > THRE * 10) && (f1 - s > THRE * 10)) break;
    }
    if(k1 == s1) return 1;

    int cnt = 0;
    QVector<Point *> org = sources.at(i)->sampleOrigin();
    int size = org.size();
    for(int j = 0; j < size; j ++)
    {
        Point* oi = org.at(j);
        Point op = *p - *oi;
        Ray sourceRay(*oi, op, 0);
        float f = distance(oi, p);
        int s = models.size();
        int k = 0;
        for(k = 0; k < s; k ++)
        {
            float s = models.at(k)->intersection(sourceRay);
            if((s > THRE * 10) && (f - s > THRE * 10)) break;
        }
        if(k == s) cnt ++;
    }
    while(!org.empty())
    {
        Point* first = org.front();
        if(first != NULL)
        {
            delete first;
            first = NULL;
        }
        org.pop_front();
    }
    return qMin(2 * cnt / (size + 0.0), 1.0);
}

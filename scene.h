#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QColor>
#include "camera.h"
#include "intensity.h"
#include "model.h"
#include "ray.h"
#include "point.h"
#include "source.h"

#define SWIDTH 3600
#define SHEIGHT 2400
#define SDEPTH 2400

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE
#define AMBIENT 0.2

class Point;
class Source;
class Ray;
class Camera;
class Model;

class Scene: public QGraphicsScene
{
    Q_OBJECT
private:

    void render();
    void initialize();

    Camera* camera;
    QImage* image;
    QRgb** pixels;
    Intensity ambient;

    QVector<Model*> models;

    int intersection(Ray, float&);

public:

    QVector<Source*> sources;
    explicit Scene(QObject *parent = 0);
    void sceneMain();// main entrance

    Intensity getAmbient() {return ambient;}
    void setAmbient(Intensity a) {ambient = a;}

    float getSourceRay(int, Point *p);
    Intensity getIntensity(Ray *);
};

#endif // SCENE_H

#ifndef MESH_H
#define MESH_H
#include "model.h"
#include "polygon.h"
#include <QVector>
#include <QString>

class Mesh : public Model
{
    struct MeshPoint;
    struct MeshTri;

    struct MeshPoint
    {
        Point point;
        QVector<MeshTri *> planes;
        Vector norm;
        MeshPoint(Point p):
            point(p), norm(0, 0, 0), planes()
        {}
        MeshPoint(const MeshPoint& m):
            point(m.point), planes(m.planes), norm(m.norm)
        {}
    };

    struct MeshTri
    {
        QVector<MeshPoint *> points;
        Vector norm;
        MeshTri(QVector<MeshPoint *>):
            points(p), norm(0, 0, 0)
        {
            Point p1 = points.at(1)->point - points.at(0)->point;
            Point p2 = points.at(2)->point - points.at(0)->point;
            Point * n= crossProduct(&p1, &p2)->normalize();
            norm = *n;
            delete n;
        }
        MeshTri(const MeshTri& m):
            points(m.points), norm(m.norm)
        {}
    };
    QVector<MeshPoint> points;
    QVector<MeshTri> triangles;

    void setNorm();

public:
    Mesh(QString);

    virtual Vector* normal(Point *);
    virtual float intersection(Ray);


    virtual ~Mesh(){}
};

#endif // MESH_H

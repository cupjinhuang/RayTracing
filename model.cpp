#include "model.h"
#include <QtCore/qmath.h>
#include <QDebug>

Model::Model(Scene *s, Color c, float refl, float diff,
             float phc, float phe, float refr, float ind):
    scene(s),
    color(c),
    reflectCo(refl), diffCo(diff),
    phongCo(phc), phongExp(phe), refractCo(refr), index(ind)
{
}

Model::Model(const Model &m):
    scene(m.scene),
    color(m.color),
    reflectCo(m.reflectCo),
    diffCo(m.diffCo),
    phongCo(m.phongCo),
    phongExp(m.phongExp),
    refractCo(m.refractCo),
    index(m.index)
{
}

Ray* Model::reflectRay(float f, Ray r)
{
    Point* p = r.getPoint(f);
    Vector* n = normal(p);
    Ray* res = r.reflectRay(f, n);
    if(p != NULL)
    {
        delete p;
        p = NULL;
    }
    if(n != NULL)
    {
        delete n;
        n = NULL;
    }
    return res;
}

Ray* Model::refractRay(float f, Ray r)
{
    Point* p = r.getPoint(f);
    Point* n = normal(p);
    float idx = index;
    if(!rayIn(p, r.getDirection()))
    {
        idx = 1.0 / index;
    }
    Ray* res = r.refractRay(f, n, 1.0 / idx);
    if(p != NULL)
    {
        delete p;
        p = NULL;
    }
    if(n != NULL)
    {
        delete n;
        n = NULL;
    }
    return res;
}

bool Model::rayIn(Point* p, Vector* v)
{
    Vector* n = normal(p);
    bool res = innerProduct(n, v) < 0;
    if(n != NULL)
    {
        delete n;
        n = NULL;
    }
    return res;
}


Intensity Model::render(Ray r)
{
    float f = intersection(r);
    Intensity i = scene->getAmbient();
    if(f <= THRE)
    {
        return Intensity(0);
    }

    Point* p1 = r.getPoint(f);
    Point p = *p1;
    if(p1 != NULL)
    {
        delete p1;
        p1 = NULL;
    }
    Vector* n = normal(&p);

    float ratio = cosine(n, r.getDirection());
    ratio *= ratio;
    if(ratio <= ITHRE) ratio = 0;
    Ray *rl = reflectRay(f, r);
    i = i + scene->getIntensity(rl) * reflectCo * (1 - ratio);
    if(rl != NULL)
    {
        delete rl;
        rl = NULL;
    }
    for(int j = 0; j < scene->sources.size(); j ++)
    {
        Source *s = scene->sources.at(j);
        Intensity si(0);

        float freq = scene->getSourceRay(j, &p);

        if(freq)
        {
            if(freq < 1)
            {
                freq = freq;
            }
            Point* o = s->getOrigin();
            Ray lt(*o, p - *o, 0);
            float f2 = distance(&p, o);
            float diff = -cosine(n, lt.getDirection());
            Ray* rl = reflectRay(f2, lt);
            float phong = -cosine(r.getDirection(), rl->getDirection());
            if(rl != NULL)
            {
                delete rl;
                rl = NULL;
            }

            si = si + s->getIntensity(f2) * diffCo * (1 - qPow(1-diff, 0.1));
            if(phong >= 0)
            {
                si = si + s->getIntensity(f2) * phongCo * qPow(phong, phongExp);
            }
            i = i + freq * si;
        }
    }
    i = i.filter(this->getColor(&p));
    if(refractCo != 0)
    {
        Ray* rr = refractRay(f, r);
        Intensity rfr = scene->getIntensity(rr) * refractCo;
        if(rr != NULL)
        {
            delete rr;
        }
        i = i + rfr;
    }
    if(n != NULL)
    {
        delete n;
        n = NULL;
    }
    return i;
}

#ifndef MODEL_H
#define MODEL_H
#include <QVector>
#include "scene.h"
#include "color.h"
#include "point.h"
#include "ray.h"

class Scene;

class Model
{
protected:
    Scene* scene;
    Color color;
    float reflectCo;
    float diffCo;
    float phongCo;
    float phongExp;
    float refractCo;
    float index;
public:    
    Model(Scene*, Color, float, float, float, float, float, float);
    Model(const Model&);

    float getReflCo() {return reflectCo;}
    float getDiffCo() {return diffCo;}
    float getPhongCo() {return phongCo;}
    float getPhongExp() {return phongExp;}
    float getRefrCo() {return refractCo;}
    float getIndex() {return index;}

    void setReflCo(float REFL) {reflectCo = REFL;}
    void setPhongCo(float PHONGCO) {phongCo = PHONGCO;}
    void setPhongExp(float PHONGEXP) {phongExp = PHONGEXP;}
    void setRefrCo(float REFR) {refractCo = REFR;}
    void setIndex(float INDEX) {index = INDEX;}
    void setScene(Scene* s) {scene = s;}
    virtual Color getColor(Point* p) {return color;} // may be overloaded by texture
    bool rayIn(Point*, Vector*);

    virtual float intersection(Ray){ return 0;}
    virtual Vector* normal(Point*){ return NULL;}
    virtual void print() {}

    Ray* reflectRay(float, Ray);
    Ray* refractRay(float, Ray);
    Intensity render(Ray);

    virtual ~Model(){}
};

#endif // MODEL_H

#ifndef OBJECT_H
#define OBJECT_H

#include "../math/vec3.h"
#include "../math/ray.h"
#include "color.h"

class Object {
  public:
    Object(Vec3 apos, Color acolor) : pos(apos), color(acolor) {}
    Vec3 getPos();
    void setPos(Vec3 apos);
    Color getColor();
    void setColor(Color acolor);
    virtual bool intersection(Ray prim_ray, Vec3 &result);
  protected:
    Vec3 pos;
    Color color;
};

#endif

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
  public:
    Ray(Vec3 ap1, Vec3 ap2);
    void eval(double t, Vec3 &result);
    Vec3 *p1,*p2;
};

#endif

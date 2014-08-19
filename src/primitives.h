#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "object.h"

#include <math.h>
#include <iostream>
#include <fstream>

class Sphere : public Object {
  public:
    Sphere(Vec3 apos, Color acolor, double aradius);
    double getRadius();
    void setRadius(double aradius);
    virtual bool intersection(Ray prim_ray, Vec3 &result);
    bool solve_quadratic(double a, double b, double c, double &x0, double &x1);
  private:
    double radius;
};

#endif

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "stdint.h"

struct sphere {
  sphere(double ax, double ay, double az, double aradius,
         double ared, double agreen, double ablue) 
        : x(ax), y(ay), z(az), radius(aradius), 
          red(ared), green(agreen), blue(ablue) {}
  double x, y, z, radius, red, green, blue;
};

class Scene {
  public:
    Scene();
    void add(sphere *new_sphere);
    std::vector<sphere*> spheres;
};

#endif

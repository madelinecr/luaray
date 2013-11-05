#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "stdint.h"

struct sphere {
  sphere(double ax, double ay, double az, double aradius) 
        : x(ax), y(ay), z(az), radius(aradius){}
  double x, y, z, radius;
};

class Scene {
  public:
    Scene();
    void add(sphere *new_sphere);
    std::vector<sphere*> spheres;
};

#endif

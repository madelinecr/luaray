#ifndef SCENE_H
#define SCENE_H

#include "vec3.h"

#include <vector>
#include "stdint.h"

struct sphere {
  sphere(double ax, double ay, double az, double aradius,
         double ared, double agreen, double ablue) 
        : x(ax), y(ay), z(az), radius(aradius), 
          red(ared), green(agreen), blue(ablue) {}
  double x, y, z, radius, red, green, blue;
};

struct light {
  light(Vec3 *apos, double anintensity) : pos(apos), intensity(anintensity) {}
  Vec3 *pos;
  double intensity;
};

class Scene {
  public:
    Scene();
    void add(sphere *asphere);
    void add(light *alight);
    std::vector<sphere*> spheres;
    std::vector<light*> lights;
};

#endif

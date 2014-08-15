#ifndef VIEW_H
#define VIEW_H

#include "stdint.h"

#include "vec3.h"
#include "ray.h"

#define FOV 30;
#define CAM_DISTANCE 100.0f; // distance the camera is from 0,0,0

struct pixel;
struct sphere;
class Scene;

class Camera {
  public:
    Camera(uint16_t const width, uint16_t const height, Scene *scene);
    void render();
  private:
    void trace(const uint16_t x, const uint16_t y, pixel &pix);
    bool solve_quadratic(double a, double b, double c, double &x0,
                                double &x1);

    bool intersection(sphere object, Ray &prim_ray, Vec3 &result);
    Scene *scene;
    unsigned int width, height;
    pixel **pixels;
};

#endif

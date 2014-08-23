#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include "stdint.h"

#include "vec3.h"
#include "ray.h"
#include "object.h"

#define SKY_INTENSITY 0.2f
#define SKY_BLUE 2
#define FOV 30
#define CAM_DISTANCE 100.0f // distance the camera is from 1,0,0

struct pixel;
struct sphere;
class Scene;

typedef std::shared_ptr<Object> objptr;

class Camera {
  public:
    Camera(uint16_t const width, uint16_t const height, Scene *scene);
    void render();
  private:
    void trace(const uint16_t x, const uint16_t y, pixel &pix);
    bool shadow(const Ray shadow_ray, const objptr object);

    Scene *scene;
    unsigned int width, height;
    pixel **pixels;
};

#endif

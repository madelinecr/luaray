#ifndef VIEW_H
#define VIEW_H

#include "stdint.h"

#include "../math/vec3.h"
#include "../math/ray.h"

#define SKY_INTENSITY 0.2f
#define SKY_BLUE 2
#define FOV 30
#define CAM_DISTANCE 100.0f // distance the camera is from 1,0,0

struct pixel;
struct sphere;
class Scene;

class Camera {
  public:
    Camera(uint16_t const width, uint16_t const height, Scene *scene);
    void render();
  private:
    void trace(const uint16_t x, const uint16_t y, pixel &pix);

    Scene *scene;
    unsigned int width, height;
    pixel **pixels;
};

#endif

#ifndef SCENE_H
#define SCENE_H

#include "../math/vec3.h"
#include "object.h"

#include <vector>
#include "stdint.h"

struct light {
  light(Vec3 *apos, double anintensity) : pos(apos), intensity(anintensity) {}
  Vec3 *pos;
  double intensity;
};

class Scene {
  public:
    Scene();
    void add_object(Object *anobject);
    void add_light(light *alight);
    std::vector<Object*> objects;
    std::vector<light*> lights;
};

#endif

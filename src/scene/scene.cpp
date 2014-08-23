#include "scene.h"
#include <iostream>

Scene::Scene(){}

void Scene::add_object(Object* anobject) {
  auto object_ptr = std::shared_ptr<Object>(anobject);
  objects.push_back(object_ptr);
}

void Scene::add_light(light *alight) {
  auto light_ptr = std::shared_ptr<light>(alight);
  lights.push_back(light_ptr);
}

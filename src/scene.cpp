#include "scene.h"
#include <iostream>

Scene::Scene(){}

void Scene::add_sphere(sphere *asphere) {
  spheres.push_back(asphere);  
  std::cout << "sphere pushed" << std::endl;
}

void Scene::add_light(light *alight) {
  lights.push_back(alight);
  std::cout << "light pushed" << std::endl;
}

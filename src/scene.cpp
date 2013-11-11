#include "scene.h"
#include <iostream>

Scene::Scene(){}

void Scene::add(sphere *asphere) {
  spheres.push_back(asphere);  
  std::cout << "sphere pushed" << std::endl;
}

void Scene::add(light *alight) {
  lights.push_back(alight);
  std::cout << "light pushed" << std::endl;
}

#include "scene.h"
#include <iostream>

Scene::Scene(){}

void Scene::add(sphere *new_sphere) {
  spheres.push_back(new_sphere);  
  std::cout << "sphere pushed" << std::endl;
}

#include "camera.h"
#include "scene.h"
#include "bitmap.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
  if(argc == 3) {
    Scene scene;
    scene.add(new sphere(150, 500, 20, 35, 2, 0, 3));
    scene.add(new sphere(300, 500, 20, 95, 0, 1, 2));
    //scene.add(new light(new Vec3(-300, 450, 20), 3));
    scene.add(new light(new Vec3(300, -500, 20), 8));
    Camera cam(atoi(argv[1]), atoi(argv[2]), &scene);
    cam.render();
  } else {
    cout << "raytrace" << endl;
    cout << "Usage: raytrace width height" << endl << endl;
  }
  return 0;
}

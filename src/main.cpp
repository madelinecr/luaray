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
    scene.add(new sphere(atoi(argv[1])/2, (atoi(argv[2])-100)/2, 20, 82, 2, 0, 3));
    scene.add(new sphere(300, 500, 20, 25, 0, 1, 2));
    Camera cam(atoi(argv[1]), atoi(argv[2]), &scene);
    cam.render();
  } else {
    cout << "raytrace" << endl;
    cout << "Usage: raytrace width height" << endl << endl;
  }
  return 0;
}

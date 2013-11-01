#include <iostream>
#include "view.h"
#include "bitmap.h"
#include <fstream>
#include <stdlib.h>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
  if(argc == 3) {
    View view(atoi(argv[1]), atoi(argv[2]));
    view.render();
  } else {
    cout << "raytrace" << endl;
    cout << "Usage: raytrace width height" << endl << endl;
  }
  return 0;
}

#ifndef VIEW_H
#define VIEW_H

#include "stdint.h"

struct pixel;

class View {
  public:
    View(unsigned int const width, unsigned int const height);
    void render();
  private:
    unsigned int width, height;
    pixel ** pixels;
};

#endif

#ifndef COLOR_H
#define COLOR_H

#include "stdint.h"

class Color {
  public:
    Color(uint16_t ared, uint16_t agreen, uint16_t ablue)
         : red(ared), green(agreen), blue(ablue) { }
    uint16_t r();
    uint16_t g();
    uint16_t b();
    void setRGB(uint16_t ared, uint16_t agreen, uint16_t ablue);
  private:
    uint16_t red, green, blue;
};

#endif

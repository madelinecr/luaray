#include "color.h"

uint16_t Color::r() {
  return red;
}

uint16_t Color::g() {
  return green;
}

uint16_t Color::b() {
  return blue;
}

void Color::setRGB(uint16_t ared, uint16_t agreen, uint16_t ablue) {
  red = ared;
  green = agreen;
  blue = ablue;
}

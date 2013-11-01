#include "view.h"
#include "pixel.h"
#include "bitmap.h"
#include <iostream>
#include <fstream>

using namespace std;

View::View(unsigned int const width, unsigned int const height) {
  this->width = width;
  this->height = height;
  this->pixels = new pixel*[height];
  for(int y = 0; y < height; y++) {
    this->pixels[y] = new pixel[width];
  }
  return;
}

void View::render() {
  for(uint16_t y = 0; y < height; y++) {
    for(uint16_t x = 0; x < width; x++) {
      this->pixels[y][x].green = x;
      this->pixels[y][x].blue = y;
      this->pixels[y][x].red = 5;
    }
  }

  Bitmap bitmap(width, height);
  bitmap.write(this->pixels);
  bitmap.to_disk((char*)("bitmap.bmp"));

  cout << "resolution is " << width << "x" << height << endl;
  return;
}

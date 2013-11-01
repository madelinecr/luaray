#ifndef BITMAP_H
#define BITMAP_H

#include "stdint.h"

#define BMP_HEADERS_SIZE 54
#define BMP_TYPE 0x4D42
#define INFOHEADER_SIZE 40
#define COLORPLANES 1
#define BPP 24
#define COMPRESSION 0
#define HORIZONTAL_RES 2835
#define VERTICAL_RES 2835
#define COLORS_NUMBER 0
#define IMPORTANT_COLORS 0

struct pixel;

struct bmp {
  // header
  uint16_t header_field;
  uint32_t size;
  char *reserved1;
  char *reserved2;
  uint32_t pixelgrid_addr;
  // bitmapinfoheader
  uint32_t infoheader_size;
  uint32_t width;
  uint32_t height;
  uint16_t colorplanes;
  uint16_t bpp;
  uint32_t compression;
  uint32_t image_size;
  uint32_t horizontal_res;
  uint32_t vertical_res;
  uint32_t colors_number;
  uint32_t important_colors;
  // linear list of pixels
  char* pixels;
};

class Bitmap {
  public:
    Bitmap(uint32_t const width, uint32_t const height);
    void write(pixel ** data);
    void to_disk(char* const filename);
  private:
    bmp bmp_data;
    uint32_t pixelgrid_size;
};

#endif

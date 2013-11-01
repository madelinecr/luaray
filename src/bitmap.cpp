#include "bitmap.h"
#include "pixel.h"
#include <fstream>

Bitmap::Bitmap(uint32_t const width, uint32_t const height) {
  uint32_t size = width*height*4;
  pixelgrid_size = size;
  // init header
  bmp_data.header_field = BMP_TYPE;
  bmp_data.size = BMP_HEADERS_SIZE + pixelgrid_size;
  bmp_data.reserved1 = new char[2];
  bmp_data.reserved2 = new char[2];
  bmp_data.pixelgrid_addr = BMP_HEADERS_SIZE;
  // init bitmapinfoheader
  bmp_data.infoheader_size = INFOHEADER_SIZE;
  bmp_data.width = width;
  bmp_data.height = height;
  bmp_data.colorplanes = COLORPLANES;
  bmp_data.bpp = BPP;
  bmp_data.compression = COMPRESSION;
  bmp_data.image_size = size;
  bmp_data.horizontal_res = HORIZONTAL_RES;
  bmp_data.vertical_res = VERTICAL_RES;
  bmp_data.colors_number = COLORS_NUMBER;
  bmp_data.important_colors = IMPORTANT_COLORS;
  // init pixel array
  bmp_data.pixels = new char[bmp_data.image_size];
  return;
}

void Bitmap::write(pixel ** data) {
  int i = 0;
  for(int y = 0; y < bmp_data.height; y++) {
    for(int x = 0; x < bmp_data.width; x++) {
      bmp_data.pixels[ i ] = static_cast<char>(data[y][x].red);
      bmp_data.pixels[i+1] = static_cast<char>(data[y][x].green);
      bmp_data.pixels[i+2] = static_cast<char>(data[y][x].blue);

      i = i + 3;
    }

    // pad out to multiples of 4 with 0x00
    if(i % 4 != 0) {
      uint16_t padbyte_count = i % 4;

      for(int bytes = 0; bytes < padbyte_count; bytes++) {
        bmp_data.pixels[i + bytes] = 0x00; // padding bytes
      }
      i = i + padbyte_count;
    }
  }
  return;
}

void Bitmap::to_disk(char* const filename) {
  std::ofstream ofs;
  ofs.open(filename, std::ofstream::out | std::ofstream::binary);
  
  // write header
  ofs.write(reinterpret_cast<char*>(&bmp_data.header_field), 2);
  ofs.write((char*)(&bmp_data.size), 4);
  ofs.write(bmp_data.reserved1, 2);
  ofs.write(bmp_data.reserved2, 2);
  ofs.write((char*)(&bmp_data.pixelgrid_addr), 4);

  // write bitmapinfoheader
  ofs.write((char*)(&bmp_data.infoheader_size), 4);
  ofs.write((char*)(&bmp_data.width), 4);
  ofs.write((char*)(&bmp_data.height), 4);
  ofs.write((char*)(&bmp_data.colorplanes), 2);
  ofs.write((char*)(&bmp_data.bpp), 2);
  ofs.write((char*)(&bmp_data.compression), 4);
  ofs.write((char*)(&bmp_data.image_size), 4);
  ofs.write((char*)(&bmp_data.horizontal_res), 4);
  ofs.write((char*)(&bmp_data.vertical_res), 4);
  ofs.write((char*)(&bmp_data.colors_number), 4);
  ofs.write((char*)(&bmp_data.important_colors), 4);
  
  // write pixmap
  ofs.write(bmp_data.pixels, bmp_data.image_size);

  return;
}

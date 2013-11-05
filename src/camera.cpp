#include "camera.h"
#include "scene.h"
#include "pixel.h"
#include "bitmap.h"

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

Ray::Ray(Vec3& ap1, Vec3& ap2) {
  p1 = &ap1;
  p2 = &ap2;
  return;
}

void Ray::eval(double t, Vec3 &result) {
  Vec3 scalar(0, 0, t);
  result = *p1 + (p2->multiply(scalar));
  return;
  
 // result.m_x = result.m_x + tmp_result.m_x;
 // result.m_y = result.m_y + tmp_result.m_y;
 // result.m_z = result.m_z + tmp_result.m_z;
  //result = *p1 + (p2->multiply(scalar));
}

Camera::Camera(uint16_t const width, uint16_t const height, Scene *scene) {
  this->scene = scene;
  this->width = width;
  this->height = height;
  this->pixels = new pixel*[height];
  for(int y = 0; y < height; y++) {
    this->pixels[y] = new pixel[width];
  }
  return;
}

void Camera::render() {
  for(uint16_t y = 0; y < height; y++) {
    for(uint16_t x = 0; x < width; x++) {
      pixel pix = { 0, 0, 0 };
      trace(x, y, pix);
      pixels[y][x].green = pix.green;
      pixels[y][x].red = pix.red;
      pixels[y][x].blue = pix.blue;
    }
  }

  Bitmap bitmap(width, height);
  bitmap.write(this->pixels);
  bitmap.to_disk((char*)("bitmap.bmp"));

  cout << "resolution is " << width << "x" << height << endl;
  return;
}

// ----------------------------------------------------------------------------
// Private methods
// ----------------------------------------------------------------------------

void Camera::trace(const uint16_t x, const uint16_t y, pixel &pix) {
  Vec3 p1(x, y, 0);
  Vec3 p2(0, 0, 1);
  Ray prim_ray(p1, p2);

  for(int i = 0; i < scene->spheres.size(); i++) {
    Vec3 point(0, 0, 0);
    //cout << &prim_ray << ":";
    //cout << "prim_ray.p1 " << prim_ray.p1->m_x << "," << prim_ray.p1->m_y << "," 
    //     << prim_ray.p1->m_z << endl;
    if(!intersection(*scene->spheres[i], prim_ray, point)) return;
    else {
      sphere *s = scene->spheres[i]; 
      Vec3 light(Vec3(-50, -50, -50));
      Vec3 center(s->x, s->y, s->z);

      point.normalize();
      light.normalize();
      center.normalize();

      Vec3 normal = point - center;

      double angle = normal.dot(light);
      if(angle <= 0.1f) return;

      cout << "angle " << angle << endl;

      pix.red =  angle * 4;
      pix.green = angle * 4;// * angle + 150;
      pix.blue = angle * 4;// * angle + 150;
      //pix.red = point.m_x*80;
      //pix.green = point.m_y*80;
      //pix.blue = point.m_z*80;
    }
  }
  return;
}

bool Camera::solve_quadratic(double a, double b, double c, 
                                    double &x0, double &x1) {
  double discr = b * b - 4 * a * c;
  if(discr < 0) return false;
  else if(discr == 0) x0 = x1 = - 0.5 * b / a;
  else {
    double q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
    x0 = q / a;
    x1 = c / q;
  }
  if(x0 > x1) std::swap(x0, x1);
  return true;
}

bool Camera::intersection(sphere object, Ray &prim_ray, Vec3 &result) {
  //cout << "prim_ray " << prim_ray.m_x << "," << prim_ray.m_y << "," 
  //     << prim_ray.m_z << endl;
  //cout << &prim_ray << ":";

  //cout << "prim_ray.p1 " << prim_ray.p1->m_x << "," << prim_ray.p1->m_y << "," 
  //     << prim_ray.p1->m_z << endl;
  //cout << "prim_ray.p2 " << prim_ray.p2->m_x << "," << prim_ray.p2->m_y << "," 
  //     << prim_ray.p2->m_z << endl;

  double t0, t1;
  Vec3 obj_center(object.x, object.y, object.z);

  //cout << "obj_center " << obj_center.m_x << "," << obj_center.m_y << "," 
  //     << obj_center.m_z << endl;

  Vec3 L = (*prim_ray.p1) - obj_center;
  L.normalize();

  //cout << "L " << L.m_x << "," << L.m_y << "," 
  //     << L.m_z << endl;


  double a = prim_ray.p2->dot(*prim_ray.p2);
  //prim_ray.p2->normalize();
  double b = 2 * prim_ray.p2->dot(L);
  double c = L.dot(L) - (object.radius * object.radius);
  //cout << "a " << a << " b " << b << " c " << c <<endl;

  if(!solve_quadratic(a, b, c, t0, t1)) {
    return false;
  } else {
    prim_ray.eval(t0, result);
    return true;
  }
}

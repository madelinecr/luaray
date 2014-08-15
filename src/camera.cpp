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

/**
 * For item in scene, check if intersection
 * if intersection, cast shadow ray based on normal of item
 */
void Camera::trace(const uint16_t x, const uint16_t y, pixel &pix) {
  Vec3 p1(x, y, 0);
  Vec3 p2(0, 0, 1);
  Ray prim_ray(p1, p2);

  for(int i = 0; i < scene->spheres.size(); i++) {
    for(int l = 0; l < scene->lights.size(); l++) {

      Vec3 point(0, 0, 0);
      if(intersection(*scene->spheres[i], prim_ray, point)) {
        sphere *s = scene->spheres[i]; 
        light *current_light = scene->lights[l];
        Vec3 center(s->x, s->y, s->z);
        Vec3 lightdir(*(current_light->pos));

        Vec3 shadow_p1(point);
        Vec3 shadow_p2(lightdir);

        Ray shadow_ray(shadow_p1, shadow_p2);
        bool in_shadow = false;

        for(int k = 0; k < scene->spheres.size(); k++) {
          Vec3 shadow_point(0, 0, 0);
          if(i == k) {
            break;
          }
          if(intersection(*scene->spheres[k], shadow_ray, shadow_point)) {
#ifdef DEBUG
            cout << "intersection for " << i << " with " << k  << endl;
            cout << "shadow point ";
            shadow_point.debug();
            cout << "shadow p1 ";
            shadow_ray.p1->debug();
            cout << "shadow p2 ";
            shadow_ray.p2->debug();
#endif
            in_shadow = true;
          } else {
            //cout << "out of shadow" << endl;
          }
        }

        point.normalize();
        lightdir.normalize();
        center.normalize();

        Vec3 normal = point - center;

#ifdef DEBUG
        cout << "shadow p1 ";
        shadow_ray.p1->debug();
        cout << "shadow p2 ";
        shadow_ray.p2->debug();
#endif


        double angle = lightdir.dot(normal);
        if(angle >= 0.1f && !in_shadow) {
          pix.red = pix.red + s->red * angle * current_light->intensity;
          pix.green = pix.green + s->green * angle * current_light->intensity;
          pix.blue = pix.blue + s->blue * angle * current_light->intensity;
        }
      }
    }
  }
  return;
}

bool Camera::solve_quadratic(double a, double b, double c, 
                                    double &x0, double &x1) {
  double discr = b * b - 4 * a * c;
  if(discr < 0) {
    return false;
  } else if(discr == 0) {
    x0 = x1 = - 0.5 * b / a;
  } else {
    double q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
    x0 = q / a;
    x1 = c / q;
  }
  if(x0 > x1) std::swap(x0, x1);
  return true;
}

bool Camera::intersection(sphere object, Ray &prim_ray, Vec3 &result) {
  double t0, t1;
  Vec3 obj_center(object.x, object.y, object.z);

  Vec3 L = (*prim_ray.p1) - obj_center;
  L.normalize();

  double a = prim_ray.p2->dot(*prim_ray.p2);
  double b = 2 * prim_ray.p2->dot(L);
  double c = L.dot(L) - (object.radius * object.radius);

  if(!solve_quadratic(a, b, c, t0, t1)) {
    return false;
  } else {
    prim_ray.eval(t0, result);
    return true;
  }
}

#include "camera.h"
#include "scene.h"
#include "pixel.h"
#include "bitmap.h"

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

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

/**
 * Finds RGB values for each pixel in the camera display area, tracing a ray
 * into the scene and writing these to disk in a bitmap.
 */
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

  if(scene->lights.size() == 1) {
    if(scene->lights[0]->pos->m_x == x && scene->lights[0]->pos->m_y == y) {
      pix.red = 255;
      pix.green = 255;
      pix.blue = 255;
      return;
    }
  }

  bool interception = false;
  for(int i = 0; i < scene->spheres.size(); i++) {
    for(int l = 0; l < scene->lights.size(); l++) {

      Vec3 point(0, 0, 0);
      if(intersection(*scene->spheres[i], prim_ray, point)) {
        interception = true;
        sphere *s = scene->spheres[i];
        light *current_light = scene->lights[l];
        Vec3 light_pos(*scene->lights[l]->pos);
        Vec3 sphere_pos(*scene->spheres[i]->pos);
        Vec3 light_localpos = light_pos - sphere_pos;
        Vec3 normal = point - sphere_pos;

        light_localpos.normalize();
        normal.normalize();
        double angle = light_localpos.dot(normal);

        if(angle >= 0.01f) {
          pix.red = pix.red + s->red * angle * current_light->intensity;
          pix.green = pix.green + s->green * angle * current_light->intensity;
          pix.blue = pix.blue + s->blue * angle * current_light->intensity;
        }

//        Vec3 shadow_p1(point);
//        Vec3 shadow_p2(lightdir);
//
//        Ray shadow_ray(shadow_p1, shadow_p2);
//        bool in_shadow = false;
//
//        for(int k = 0; k < scene->spheres.size(); k++) {
//          Vec3 shadow_point(0, 0, 0);
//          if(i == k) {
//            break;
//          }
//          if(intersection(*scene->spheres[k], shadow_ray, shadow_point)) {
//            //in_shadow = true;
//          } else {
//            //cout << "out of shadow" << endl;
//          }
//        }

//        double angle = lightdir.dot(normal);
//        if(angle >= 0.01f && !in_shadow) {
//          //pix.red = pix.red + s->red * angle * current_light->intensity;
//          //pix.green = pix.green + s->green * angle * current_light->intensity;
//          //pix.blue = pix.blue + s->blue * angle * current_light->intensity;
//        }
      }
    }
  }
  if(interception == false) {
    pix.red = SKY_INTENSITY * y;
    pix.green = SKY_INTENSITY * y;
    pix.blue = SKY_INTENSITY * y * SKY_BLUE;
  }
  return;
}

/**
 * Helper function, solves a quadratic equation. This is used to calculate
 * the intersection of rays and spheres, as a sphere is a quadratic function
 */
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

/**
 * Calculates whether a ray intersects with a sphere. Returns true or false,
 * storing the collision point in result if true.
 */
bool Camera::intersection(sphere object, Ray &prim_ray, Vec3 &result) {
  double t0, t1;
  Vec3 obj_center(*object.pos);

  Vec3 L = (*prim_ray.p1) - obj_center;

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

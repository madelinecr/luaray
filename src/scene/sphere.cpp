#include "sphere.h"

Sphere::Sphere(Vec3 apos, Color acolor, double aradius) : Object(apos, acolor) {
  radius = aradius;
}

double Sphere::getRadius() {
  return radius;
}

void Sphere::setRadius(double aradius) {
  radius = aradius;
}

/**
 * Calculates whether a ray intersects with a sphere. Returns true or false,
 * storing the collision point in result if true.
 */
bool Sphere::intersection(Ray prim_ray, Vec3 &result) {
  double t0, t1;
  Vec3 obj_center(pos);

  Vec3 L = (*prim_ray.p1) - obj_center;

  double a = prim_ray.p2->dot(*prim_ray.p2);
  double b = 2 * prim_ray.p2->dot(L);
  double c = L.dot(L) - (radius * radius);

  if(!solve_quadratic(a, b, c, t0, t1)) {
    return false;
  } else {
    prim_ray.eval(t0, result);
    return true;
  }
}

/**
 * Helper function, solves a quadratic equation. This is used to calculate
 * the intersection of rays and spheres, as a sphere is a quadratic function
 */
bool Sphere::solve_quadratic(double a, double b, double c,
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

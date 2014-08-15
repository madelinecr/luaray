#include "ray.h"

/**
 * Creates a new ray, at ap1 pointing in direction ap2
 */
Ray::Ray(Vec3& ap1, Vec3& ap2) {
  p1 = &ap1;
  p2 = &ap2;
  return;
}

/**
 * Walks down the ray, returning the point along the ray distance t in the
 * direction of p2
 */
void Ray::eval(double t, Vec3 &result) {
  Vec3 scalar(0, 0, t);
  result = *p1 + (p2->multiply(scalar));
  return;
}


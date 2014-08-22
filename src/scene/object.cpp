#include "object.h"

Vec3 Object::getPos() {
  return pos;
}

void Object::setPos(Vec3 apos) {
  pos = apos;
}

Color Object::getColor() {
  return color;
}

void Object::setColor(Color acolor) {
  color = acolor;
}

bool Object::intersection(Ray prim_ray, Vec3 &result) {
  return false;
}

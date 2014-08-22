#include "vec3.h"

#include <math.h>

#ifdef DEBUG
#include <iostream>
#endif

Vec3::Vec3(Vec3 const &avec) {
  m_x = avec.m_x;
  m_y = avec.m_y;
  m_z = avec.m_z;
}

double Vec3::dot(Vec3 v) {
  return (m_x*v.m_x) + (m_y*v.m_y) + (m_z*v.m_z);
}

Vec3 Vec3::operator-(const Vec3& other) {
  Vec3 result(0, 0, 0);
  result.m_x = m_x - other.m_x;
  result.m_y = m_y - other.m_y;
  result.m_z = m_z - other.m_z;
  return result;
}

Vec3 Vec3::operator+(const Vec3& other) {
  Vec3 result(0, 0, 0);
  result.m_x = m_x + other.m_x;
  result.m_y = m_y + other.m_y;
  result.m_z = m_z + other.m_z;
  return result;
}

Vec3 Vec3::multiply(const Vec3& other) {
  Vec3 result(0, 0, 0);
  result.m_x = m_x * other.m_x;
  result.m_y = m_y * other.m_y;
  result.m_z = m_z * other.m_z;
  return result;
}

#ifdef DEBUG
void Vec3::debug() {
  std::cout << "vec: " << m_x << " " << m_y << " " << m_z << std::endl;
}
#endif

void Vec3::normalize() {
  double length = sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
  m_x = m_x / length;
  m_y = m_y / length;
  m_z = m_z / length;
}

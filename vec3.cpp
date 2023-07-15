#include <cmath>
#include "vec3.h"

Vec3::Vec3(): e{0.0, 0.0, 0.0} {}
Vec3::Vec3(float x, float y, float z): e{x, y, z} {};

float Vec3::operator[](int i) const { return e[i]; }
float& Vec3::operator[](int i) { return e[i]; }

Vec3 operator+(const Vec3& u, const Vec3& v) { return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]); }
Vec3 operator-(const Vec3& u, const Vec3& v) { return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]); }
Vec3 operator*(const Vec3& v, float s) { return Vec3(v[0] * s, v[1] * s, v[2] * s); }
Vec3 operator*(float s, const Vec3& u) { return u * s; }
Vec3 operator*(const Vec3& u, const Vec3& v) { return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]); }
Vec3 operator/(const Vec3& v, float s) { return Vec3(v[0] / s, v[1] / s, v[2] / s); }

Vec3& Vec3::operator+=(const Vec3& v) {
  e[0] += v[0];
  e[1] += v[1];
  e[2] += v[2];
  return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
  e[0] -= v[0];
  e[1] -= v[1];
  e[2] -= v[2];
  return *this;
}

Vec3& Vec3::operator*=(float s) {
  e[0] *= s;
  e[1] *= s;
  e[2] *= s;
  return *this;
}

Vec3& Vec3::operator/=(float s) {
  e[0] /= s;
  e[1] /= s;
  e[2] /= s;
  return *this;
}

float Vec3::length_squared() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
float Vec3::length() const { return std::sqrt(length_squared()); }


void Vec3::rotate_y(float a) {
  float tmp0(e[0]);
  const float sina = std::sin(a);
  const float cosa = std::cos(a);
  e[0] = e[0] * cosa + e[2] * sina;
  e[2] = e[2] * cosa - tmp0 * sina;
}

float dot(const Vec3&u, const Vec3& v) { return u[0] * v[0] + u[1] * v[1] + u[2] * v[2]; }

Vec3 cross(const Vec3& u, const Vec3& v) {
  return Vec3(u[1] * v[2] - u[2] * v[1],
      u[2] * v[0] - u[0] * v[2],
      u[0] * v[1] - u[1] * v[0]);
}

Vec3 unit_vector(Vec3 v) { return v / v.length(); }

/*
void rotate(Vec3& u, float angle) {
  float s = std::sin(angle);
  float c = std::cos(angle);
  float tempx = u[0];
  u[0] = u[0] * c - u[1] * s;
  u[1] = tempx * s + u[1] * c;
}
*/

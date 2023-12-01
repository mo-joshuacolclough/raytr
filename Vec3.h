#pragma once

#include <array>

class Vec3 {
 public:
  Vec3();
  Vec3(float x, float y, float z);
  
  Vec3(const Vec3& other);
  Vec3& operator=(const Vec3& other);

  const float& x() const { return e[0]; }
  float& x() { return e[0]; }
  const float& y() const { return e[1]; }
  float& y() { return e[1]; }
  const float& z() const { return e[2]; }
  float& z() { return e[2]; }

  float operator[](int i) const;
  float& operator[](int i);
  Vec3& operator+=(const Vec3& v);
  Vec3& operator-=(const Vec3& v);
  Vec3& operator*=(float s);
  Vec3& operator/=(float s);

  float length() const;
  float length_squared() const;

  void rotate_y(float a);
 private:
  std::array<float, 3> e;
};

Vec3 operator+(const Vec3& u, const Vec3& v);

Vec3 operator*(const Vec3& u, float s);
Vec3 operator*(float s, const Vec3& u);
Vec3 operator*(const Vec3& u, const Vec3& v);

Vec3 operator/(const Vec3&u, float s);
Vec3 operator-(const Vec3& u, const Vec3& v);

float dot(const Vec3& u, const Vec3& v);
Vec3 cross(const Vec3 &u, const Vec3& v);
Vec3 unit_vector(Vec3 v);

void rotate(Vec3& u, float angle);

using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color


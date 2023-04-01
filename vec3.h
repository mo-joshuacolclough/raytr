#ifndef VEC3_H
#define VEC3_H

class Vec3 {
 public:
  float e[3];

  Vec3();
  Vec3(float x, float y, float z);
  float x() const;
  float y() const;
  float z() const;

  float operator[](int i) const;
  float& operator[](int i);
  Vec3& operator+=(const Vec3& v);
  Vec3& operator-=(const Vec3& v);
  Vec3& operator*=(float s);
  Vec3& operator/=(float s);
  float length() const;
  float length_squared() const;
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


#endif // VEC3_H

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
 private:
  Point3 o; // Origin
  Vec3 dir; // Direction
  float brightness;
 public:
  Ray();
  Ray(const Point3& origin, const Vec3& direction);
  Ray(const Point3& origin, const Vec3& direction, const float brightness);

  Point3 origin() const;
  Vec3 direction() const;
  Point3 at(float t) const;
  void reflect(const Vec3& normal,
               Vec3 new_origin,
               const float reflectivity);

  float getBrightness() const { return brightness; }
};

#endif // RAY_H

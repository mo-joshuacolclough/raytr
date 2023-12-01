#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
 private:
  Point3 o; // Origin
  Vec3 dir; // Direction
  double brightness;
 public:
  Ray();
  Ray(const Point3& origin, const Vec3& direction);
  Ray(const Point3& origin, const Vec3& direction, const double brightness);

  const Point3& origin() const;
  const Vec3& direction() const;
  Point3 at(const float t) const;
  Ray reflect(const Vec3& normal,
              const Vec3 new_origin,
              const double reflectivity) const;

  double getBrightness() const { return brightness; }
};

#endif // RAY_H

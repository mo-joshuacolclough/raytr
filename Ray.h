#pragma once

#include "Vec3.h"

class Ray {
 public:
  Ray();
  Ray(const Point3& origin, const Vec3& direction);
  Ray(const Point3& origin, const Vec3& direction, const double brightness);

  const Point3& origin() const;
  const Vec3& direction() const;
  Point3 at(const float t) const;
  Ray reflect(const Vec3& normal,
              const Vec3& new_origin,
              const double reflectivity) const;

  double get_brightness() const { return brightness_; }
 private:
  Point3 origin_; // Origin
  Vec3 dir_; // Direction
  double brightness_;
};


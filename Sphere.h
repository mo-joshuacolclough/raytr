#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Body.h"

class Sphere : public Body {
 public:
  Sphere(const Point3& centre, const Color& color, const float reflectivity, const float radius);
  float hit(const Ray& r) const override;
  Vec3 normal_at(const Point3& pos) const override;
  Color color_at(const Point3& pos) const override;
 private:
  const float r_;
};


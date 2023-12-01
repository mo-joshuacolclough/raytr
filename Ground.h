#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Body.h"

class Ground : public Body {
 public:
  Ground(const float yval, const Color& color, const float reflectivity);
  float hit(const Ray& r) const override;
  Vec3 normal_at(const Point3& pos) const override;
  Color color_at(const Point3& pos) const override;
};


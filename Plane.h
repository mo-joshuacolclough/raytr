#pragma once

#include "Vec3.h"
#include "Body.h"
#include "Ray.h"

// pos = point that lies on the plane
// norm = normal vector
// rot = Vector tangent to the plane that defines an "up". Rotation around normal vec
// dims = dimensions relative to rot
class Plane : public Body {
 public:
  Plane(const Point3& position, const Color& color, const float reflectivity,
       const Vec3& normal, const float rotation, const float width, const float height);
  float hit(const Ray& r) const override;
  Vec3 normal_at(const Point3& pos) const override;
  Color color_at(const Point3& pos) const override;
 private:
  Vec3 norm_;
  float dims_[2];
};


#ifndef PLANE_H
#define PLANE_H

#include "vec3.h"
#include "body.h"
#include "ray.h"

// pos = point that lies on the plane
// norm = normal vector
// rot = Vector tangent to the plane that defines an "up". Rotation around normal vec
// dims = dimensions relative to rot
class Plane : public Body {
 private:
  Color col;
  Vec3 norm;
  float dims[2];
 public:
  Plane(unsigned int id, float reflectivity, Point3 position, Color color, Vec3 normal, float rotation, float width, float height);
  float hit(const Ray& r) const override;
  Vec3 normal_at(const Point3& pos) const override;
  Color color_at(const Point3& pos) const override;
};

#endif // PLANE_H

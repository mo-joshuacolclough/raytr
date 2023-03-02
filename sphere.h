#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "body.h"

class Sphere : public Body {
 public:
  float r;
  Color col;
  Sphere(unsigned int id, float reflectivity_, Point3 centre, float radius, Color color);
  float hit(const Ray& r) const override;
  Vec3 normal_at(const Point3& pos) const override;
  Color color_at(const Point3& pos) const override;
};

#endif // SPHERE_H

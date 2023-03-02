#ifndef TORUS_H
#define TORUS_H

#include "vec3.h"
#include "ray.h"
#include "body.h"

class Torus : public Body {
 public:
  float r;

  float hit(const Ray& r) const override;
  Vec3 normal_at(const Point3& pos) const override;
};
#endif // TORUS_H

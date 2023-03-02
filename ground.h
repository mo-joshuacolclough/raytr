#ifndef GROUND_H
#define GROUND_H

#include "vec3.h"
#include "ray.h"
#include "body.h"

class Ground : public Body {
 public:
  Color col;
  Ground(unsigned int id, float yval, Color color);
  float hit(const Ray& r) const override;
  Vec3 normal_at(const Point3& pos) const override;
  Color color_at(const Point3& pos) const override;
};

#endif // GROUND_H

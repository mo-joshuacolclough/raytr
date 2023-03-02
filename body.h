#ifndef BODY_H
#define BODY_H

#include "vec3.h"
#include "ray.h"

// A body is any object that can be hit by a ray

class Body {
 public:
  Point3 pos;
  unsigned int id;
  float reflectivity;

  // Returns if a ray will hit, and if so what shade
  virtual float hit(const Ray& r) const = 0;
  virtual Vec3 normal_at(const Point3& pos) const = 0;
  virtual Color color_at(const Point3& pos) const = 0;
};

#endif // BODY_H

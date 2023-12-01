#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Color.h"

// A body is any object that can be hit by a ray

class Body {
 public:
  Body(const Point3& pos, const Color& col, const float reflectivity) :
    pos_(pos), base_col_(col), reflectivity_(reflectivity)
  {
    static size_t s_last_id = 0;
    id_ = s_last_id++;
  }

  // Returns if a ray will hit, and if so what shade
  virtual float hit(const Ray& r) const = 0;
  virtual Vec3 normal_at(const Point3& pos) const = 0;
  virtual Color color_at(const Point3& pos) const = 0;

  size_t get_id() const { return id_; }
  Point3& get_pos() { return pos_; }
  const Point3& get_pos() const { return pos_; }
  const Color& get_base_color() const { return base_col_; }

  float get_reflectivity() const { return reflectivity_; }

 private:
  Point3 pos_;
  const Color base_col_;
  size_t id_;
  const float reflectivity_;
};


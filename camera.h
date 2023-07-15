#pragma once

#include "common.h"
#include "ray.h"
#include "vec3.h"

// (maths from https://raytracing.github.io/books/RayTracingInOneWeekend.html/)

class Camera {
 public:
  Camera();
  ~Camera();
  Camera(const Camera&) = delete;

  void calculate_ray_directions();
  Ray make_ray(size_t p_idx) const;

  // Movement
  void rotate_left();
  void rotate_right();
  void move_forward();
  void move_back();
  void strafe_left();
  void strafe_right();
  void move_up();
  void move_down();

 private:
  static constexpr float viewport_height_ = 2.0;
  static constexpr float viewport_width_ = viewport_height_ * static_cast<float>(SCREEN_WIDTH)/static_cast<float>(SCREEN_HEIGHT);
  static constexpr float focal_length_ = 1.0;

  float angle_;
  Vec3 origin_;

  // Current directions of each ray. origin + direction = ray vector
  Vec3* ray_directions_;
};


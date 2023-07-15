#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "common.h"
#include "ray.h"
#include "vec3.h"

// (maths from https://raytracing.github.io/books/RayTracingInOneWeekend.html/)

class Camera {
 public:
  Camera();
  ~Camera();
  Camera(const Camera&) = delete;

  void update(const float dt);

  void calculate_ray_directions();
  Ray make_ray(size_t p_idx) const;

  // SDL
  void handle_event(const SDL_Event& event);

 private:
  // Movement
  void rotate_left(const float dt);
  void rotate_right(const float dt);
  void move_forward(const float dt);
  void move_back(const float dt);
  void strafe_left(const float dt);
  void strafe_right(const float dt);
  void move_up(const float dt);
  void move_down(const float dt);

  // void handle_mouse_motion_event() {}  // TODO


  static constexpr float viewport_height_ = 2.0;
  static constexpr float viewport_width_ = viewport_height_ * static_cast<float>(SCREEN_WIDTH)/static_cast<float>(SCREEN_HEIGHT);
  static constexpr float focal_length_ = 1.0;

  // Map of what keys are currently pressed
  std::map<SDL_Keycode, bool> keydown_;

  float angle_;
  Vec3 origin_;
  // Vec3 view_direction_;  TODO

  // Current directions of each ray. origin + direction = ray vector
  Vec3* ray_directions_;
};


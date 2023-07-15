#include <cmath>
#include <iostream>

#include "camera.h"

constexpr float CAMERA_DA = M_PI/8.0;

// -----------------------------------

Camera::Camera() :
  angle_(0.0f),
  origin_(0.0f, 0.0f, 0.0f),
  keydown_{ {SDLK_w, false}, {SDLK_s, false}, {SDLK_a, false}, {SDLK_d, false},
            {SDLK_LSHIFT, false}, {SDLK_SPACE, false} }
{
  ray_directions_ = new Vec3[SCREEN_HEIGHT * SCREEN_WIDTH];
}

Camera::~Camera() {
  delete [] ray_directions_;
}

Ray Camera::make_ray(size_t p_idx) const {
  return Ray(origin_, ray_directions_[p_idx]);
}

void Camera::calculate_ray_directions() {
  const Vec3 horizontal = Vec3(viewport_width_, 0, 0);
  const Vec3 vertical = Vec3(0, viewport_height_, 0);
  const Vec3 lower_left_corner = origin_ - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length_);
  
  float u, v;
  size_t p_idx;
  for (size_t j = 0; j < SCREEN_HEIGHT; ++j) {
    for (size_t i = 0; i < SCREEN_WIDTH; ++i) {
      u =       static_cast<float>(i)/(SCREEN_WIDTH-1);
      v = 1.0 - static_cast<float>(j)/(SCREEN_HEIGHT-1);  // Flip vertical
      p_idx = j * SCREEN_WIDTH + i;
      ray_directions_[p_idx] = lower_left_corner + u * horizontal + v * vertical - origin_;
      ray_directions_[p_idx].rotate_y(angle_);
    }
  }
}

void Camera::update() {
  for (auto& [key, is_down] : keydown_) {
    if (!is_down) continue;

    switch (key) {
      case SDLK_w:
        move_forward();
        break;
      case SDLK_s:
        move_back();
        break;
      case SDLK_a:
        strafe_left();
        break;
      case SDLK_d:
        strafe_right();
        break;
      case SDLK_SPACE:
        move_up();
        break;
      case SDLK_LSHIFT:
        move_down();
        break;
      default:
        std::cout << "KEYCODE: " << key << std::endl;
        break;
    }
  }
}

void Camera::handle_event(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
    SDL_Keycode keycode = event.key.keysym.sym;
    // First check the keycode is in the map
    if (keydown_.find(keycode) != keydown_.end()) {
      keydown_[keycode] = event.type == SDL_KEYDOWN;
    }
  }
}

// Camera movement
void Camera::rotate_left() {
  angle_ += CAMERA_DA;
  calculate_ray_directions();
}
void Camera::rotate_right() {
  angle_ -= CAMERA_DA;
  calculate_ray_directions();
}
void Camera::move_forward() {
  Vec3 dx = Vec3(0, 0, -0.05);
  dx.rotate_y(angle_);
  origin_ += dx;

  calculate_ray_directions();
}
void Camera::move_back() {
  Vec3 dx = Vec3(0, 0, 0.05);
  dx.rotate_y(angle_);
  origin_ += dx;
  calculate_ray_directions();
}
void Camera::strafe_left() {
  Vec3 dx = Vec3(-0.05, 0, 0);
  dx.rotate_y(angle_);
  origin_ += dx;
  calculate_ray_directions();
}
void Camera::strafe_right() {
  Vec3 dx = Vec3(0.05, 0, 0);
  dx.rotate_y(angle_);
  origin_ += dx;
  calculate_ray_directions();
}
void Camera::move_up() {
  Vec3 dx = Vec3(0, 0.05, 0);
  dx.rotate_y(angle_);
  origin_ += dx;
  calculate_ray_directions();
}
void Camera::move_down() {
  Vec3 dx = Vec3(0, -0.05, 0);
  dx.rotate_y(angle_);
  origin_ += dx;
  calculate_ray_directions();
}


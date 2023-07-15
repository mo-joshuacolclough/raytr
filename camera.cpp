#include "camera.h"
#include "log.h"

constexpr float CAMERA_DA = PI/8.0;


namespace {

Vec3 rotate_y(Vec3 in, float a) {
  Vec3 out;
  out[0] = in[0] * cos(a) + in[2] * sin(a);
  out[1] = in[1];
  out[2] = in[2] * cos(a) - in[0] * sin(a);
  return out;
}

}  // namespace

// -----------------------------------

Camera::Camera() :
  angle_(0.0f),
  origin_(0.0f, 0.0f, 0.0f)
{
  LOG_TR("constructor starting...");
  ray_directions_ = new Vec3[RAYX * RAYY];
  LOG_TR("construced.");
}

Camera::~Camera() {
  delete [] ray_directions_;
}

Ray Camera::make_ray(uint16_t p_idx) const {
  LOG_TR("done.");
  return Ray(origin_, ray_directions_[p_idx]);
}

void Camera::calculate_ray_directions() {
  LOG_TR("starting...");
  
  const Vec3 horizontal = Vec3(viewport_width_, 0, 0);
  const Vec3 vertical = Vec3(0, viewport_height_, 0);
  const Vec3 lower_left_corner = origin_ - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length_);
  
  float u, v;
  uint16_t p_idx;
  for (uint16_t j = 0; j < RAYY; ++j) {
    for (uint16_t i = 0; i < RAYX; ++i) {
      u = static_cast<float>(i)/(RAYX-1);
      v = static_cast<float>(j)/(RAYY-1);
      p_idx = j * RAYX + i;
      ray_directions_[p_idx] = lower_left_corner + u * horizontal + v * vertical - origin_;
      ray_directions_[p_idx] = rotate_y(ray_directions_[p_idx], angle_);
    }
  }
  LOG_TR("done.");
}

// Camera movement
void Camera::rotate_left() {
  LOG_TR("starting...");
  LOG_DEBUG("Camera moving left.");
  angle_ += CAMERA_DA;
  calculate_ray_directions();
  LOG_TR("done.");
}
void Camera::rotate_right() {
  LOG_TR("starting...");
  LOG_DEBUG("Camera moving right.");
  angle_ -= CAMERA_DA;
  calculate_ray_directions();
  LOG_TR("done.");
}
void Camera::move_forward() {
  LOG_TR("starting...");
  LOG_DEBUG("Camera moving forward.");
  origin_ += rotate_y(Vec3(0, 0, -0.25), angle_);
  LOG_DEBUG("New origin: (%.2f, %.2f, %.2f)", origin_.x(), origin_.y(), origin_.z());
  calculate_ray_directions();
  LOG_TR("done.");
}
void Camera::move_back() {
  LOG_TR("starting...");
  LOG_DEBUG("Camera moving backward.");
  origin_ += rotate_y(Vec3(0, 0, 0.25), angle_);
  calculate_ray_directions();
  LOG_TR("done.");
}
void Camera::strafe_left() {
  LOG_TR("starting...");
  LOG_DEBUG("Camera strafing left.");
  origin_ += rotate_y(Vec3(-0.25, 0, 0.0), angle_);
  calculate_ray_directions();
  LOG_TR("done.");
}
void Camera::strafe_right() {
  LOG_TR("starting...");
  LOG_DEBUG("Camera strafing right.");
  origin_ += rotate_y(Vec3(0.25, 0, 0.0), angle_);
  calculate_ray_directions();
  LOG_TR("done.");
}
void Camera::move_up() {
  LOG_TR("starting...");
  LOG_DEBUG("Camera moving up.");
  origin_ += rotate_y(Vec3(0.0, 0.25, 0.0), angle_);
  calculate_ray_directions();
  LOG_TR("done.");
}
void Camera::move_down() {
  LOG_TR("starting...");
  LOG_DEBUG("Camera moving down.");
  origin_ += rotate_y(Vec3(0.0, -0.25, 0.0), angle_);
  calculate_ray_directions();
  LOG_TR("done.");
}


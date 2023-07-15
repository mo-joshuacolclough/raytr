#pragma once

#include <cstddef>

// Shadows?
#define SHADOWS
// Reflections?
#define REFLECTIONS

constexpr size_t MAX_REFLECTIONS = 2;

constexpr float ASPECT_RATIO = 4.0/3.0; // 16.0/9.0;
constexpr size_t SCREEN_WIDTH = 600;
constexpr size_t SCREEN_HEIGHT = static_cast<size_t>(SCREEN_WIDTH/ASPECT_RATIO);

constexpr float CAMERA_MOVE_SPEED = 1.0;


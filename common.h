#pragma once

#include <cstddef>

constexpr size_t MAX_REFLECTIONS = 2;

constexpr float ASPECT_RATIO = 16.0/9.0;
constexpr size_t SCREEN_WIDTH = 1920/2.0;
constexpr size_t SCREEN_HEIGHT = static_cast<size_t>(SCREEN_WIDTH/ASPECT_RATIO);


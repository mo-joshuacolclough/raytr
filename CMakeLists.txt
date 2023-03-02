cmake_minimum_required(VERSION 3.5)

project(raytr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytr main.cpp
    vec3.h vec3.cpp
    ray.h ray.cpp
    color.h color.cpp
    body.h body.cpp
    sphere.h sphere.cpp
    light.h light.cpp
    world.h world.cpp
    ground.h ground.cpp
#    torus.h torus.cpp
#    aacube.h aacube.cpp
    plane.h plane.cpp
#    equation.h equation.cpp
    )

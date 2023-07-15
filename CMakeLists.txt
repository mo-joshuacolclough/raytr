cmake_minimum_required(VERSION 3.5)

project(raytr LANGUAGES CXX)

find_package(OpenMP REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(raytr ${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    common.h
    camera.h camera.cpp
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

add_executable(raytr ${SOURCES})
target_link_libraries(raytr PRIVATE OpenMP::OpenMP_CXX ${SDL2_LIBRARIES})


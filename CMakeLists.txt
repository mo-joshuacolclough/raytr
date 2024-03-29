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
    Camera.h Camera.cpp
    Vec3.h Vec3.cpp
    Ray.h Ray.cpp
    Color.h Color.cpp
    Body.h
    Sphere.h Sphere.cpp
    Light.h Light.cpp
    World.h World.cpp
    Ground.h Ground.cpp
#    torus.h torus.cpp
#    aacube.h aacube.cpp
    Plane.h Plane.cpp
#    equation.h equation.cpp
)

add_executable(raytr ${SOURCES})
target_link_libraries(raytr PRIVATE OpenMP::OpenMP_CXX ${SDL2_LIBRARIES})


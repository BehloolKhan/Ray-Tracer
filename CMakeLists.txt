cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RayTracer Source.cpp "Constants.h" "Canvas.h" "Sphere.h" "Vec3.h" "methods.cpp" "Vec3.cpp" "methods.h" "Sphere.cpp" "Canvas.cpp")
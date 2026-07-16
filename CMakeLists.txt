cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RayTracer main.cpp "core/Constants.h" "core/Canvas.h" "scene/Sphere.h" "core/Vec3.h" "core/methods.cpp" "core/Vec3.cpp" "core/methods.h" "scene/Sphere.cpp" "core/Canvas.cpp" "scene/Scene.h" "scene/Scene.cpp" "scene/Light.h" "scene/Light.cpp" "scene/ChildLights.h" "scene/ChildLights.cpp" "testFile.h" "scene/BoundingTree.h" "scene/boundingBox.h" "scene/BoundingTree.cpp" "scene/boundingBox.cpp")
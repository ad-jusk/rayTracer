add_executable(rayTracer "main.cpp"   "src/ray.cpp" "src/sphere.cpp" "src/plane.cpp" "src/triangle.cpp" "src/image.cpp"  "src/camera/orthogonalCamera.cpp" "src/camera/perspectiveCamera.cpp")

add_subdirectory(lib)

include_directories(lib lib/lodepng)

target_link_libraries(rayTracer lodepng)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rayTracer PROPERTY CXX_STANDARD 20)
endif()
# Add source to this project's executable.
add_executable (rayTracer    "main.cpp" "include/Vector3.h" "include/Ray.h" "include/Camera.h" "src/Camera.cpp" "include/FileUtils.h" "include/Hittable.h" "include/Sphere.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rayTracer PROPERTY CXX_STANDARD 20)
endif()

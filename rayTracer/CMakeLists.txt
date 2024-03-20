add_executable(rayTracer "main.cpp"   "src/ray.cpp" "src/sphere.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rayTracer PROPERTY CXX_STANDARD 20)
endif()
project(rayTracer)

add_executable(${PROJECT_NAME} "main.cpp"   "src/ray.cpp" "src/sphere.cpp" "src/plane.cpp" "src/triangle.cpp" "src/image.cpp"  "src/camera/orthogonalCamera.cpp" "src/camera/perspectiveCamera.cpp" "include/light/SpotLight.h")

add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib 
	${CMAKE_CURRENT_SOURCE_DIR}/lib/lodepng
)

target_link_libraries(rayTracer lodepng)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rayTracer PROPERTY CXX_STANDARD 20)
endif()
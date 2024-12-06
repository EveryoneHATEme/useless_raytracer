# CMakeList.txt : CMake project for ray_project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ray_project")

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_subdirectory(libs/raylib-5.5)

# Add source to this project's executable.
add_executable (ray_project "main.cpp" "RayClass.h" "RayClass.cpp" "Camera.h" "Camera.cpp" "Utils.h" "Utils.cpp" "Scene.h" "Scene.cpp" "Sphere.h" "Sphere.cpp" "HitPayload.h" "RenderableObject.h"  "Renderer.h" "Renderer.cpp" "Material.h")

target_link_libraries(ray_project PRIVATE raylib)

find_package(glm CONFIG REQUIRED)
target_link_libraries(ray_project PRIVATE glm::glm)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ray_project PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

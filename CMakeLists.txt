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

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp" "Camera.h" "Camera.cpp" "Renderer.h" "Renderer.cpp"  "graphics/Shader.cpp" "graphics/ShaderStorageBuffer.cpp" "graphics/Texture.cpp" "graphics/UniformBuffer.cpp" "graphics/VertexArray.cpp" "graphics/VertexBuffer.cpp" "Scene.h" "Scene.cpp" "Settings.h")

add_subdirectory(glfw REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/copy_shader.comp ${CMAKE_CURRENT_BINARY_DIR}/copy_shader.comp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment_shader.frag ${CMAKE_CURRENT_BINARY_DIR}/fragment_shader.frag COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/raytracing_shader.comp ${CMAKE_CURRENT_BINARY_DIR}/raytracing_shader.comp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex_shader.vert ${CMAKE_CURRENT_BINARY_DIR}/vertex_shader.vert COPYONLY)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

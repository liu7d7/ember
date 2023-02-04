cmake_minimum_required(VERSION 3.23)
project(ember)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glm/glm)

find_package(OpenGL REQUIRED)

include_directories(libs/glfw/include/GLFW)
include_directories(libs/glad)
include_directories(libs/glm/glm)
include_directories(include)
include_directories(libs/stb)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(ember main.cpp include/ember.h include/global.h src/ember.cpp libs/glad/glad.h libs/glad/glad.c include/engine/fbo.h src/engine/fbo.cpp include/engine/tex.h src/engine/tex.cpp libs/stb/stb_image.h include/engine/shader.h src/engine/shader.cpp include/engine/buf.h include/engine/vao.h src/engine/vao.cpp include/engine/mesh.h include/engine/draw_mode.h include/engine/glsm.h include/engine/model.h src/engine/model.cpp include/engine/camera.h include/engine/imodel.h src/engine/imodel.cpp include/engine/stb_font.h libs/stb/stb_truetype.h include/file.h include/engine/lightmap.h src/engine/camera.cpp libs/stb/stb_image_write.h src/engine/lightmap.cpp src/engine/stb_font.cpp include/impl/entity.h include/rand.h src/impl/entity.cpp include/impl/comp.h src/impl/comp.cpp include/engine/lines.h include/impl/anim.h src/impl/anim.cpp include/impl/chunk.h src/impl/chunk.cpp include/impl/world.h src/impl/world.cpp include/impl/palette.h src/engine/glsm.cpp)
target_link_libraries(ember glfw)

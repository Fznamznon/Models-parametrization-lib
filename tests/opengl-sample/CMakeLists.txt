
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)
find_path(GLM_PATH glm)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(GLM_PATH)

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  ${GLEW_LIBRARIES}
  glfw
  param-lib
  assimp
)

add_executable(opengl-sample
  opengl-sample.cpp
)
target_link_libraries(opengl-sample
  ${ALL_LIBS}
)

configure_file(SimpleFragmentShader.fragmentshader SimpleFragmentShader.fragmentshader COPYONLY)

configure_file(SimpleVertexShader.vertexshader SimpleVertexShader.vertexshader COPYONLY)

configure_file(heart.obj heart.obj COPYONLY)
configure_file(heart_start.obj heart_start.obj COPYONLY)
configure_file(heart_end.obj heart_end.obj COPYONLY)


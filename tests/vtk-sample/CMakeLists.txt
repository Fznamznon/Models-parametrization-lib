
find_package(VTK REQUIRED)
find_package(assimp REQUIRED)
include(${VTK_USE_FILE})

set(ALL_LIBS
  ${VTK_LIBRARIES}
  param-lib
  assimp
)

add_executable(VTK-sample vtk-sample.cpp)

target_link_libraries(VTK-sample
  ${ALL_LIBS}
)

configure_file(heart.vtk heart.vtk COPYONLY)
configure_file(heart_start.obj heart_start.obj COPYONLY)
configure_file(heart_end.obj heart_end.obj COPYONLY)

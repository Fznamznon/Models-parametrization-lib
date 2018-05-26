
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(TrackballCamera example_trackballcamera.cpp)
target_link_libraries(TrackballCamera ${VTK_LIBRARIES})

configure_file(heart.vtk heart.vtk COPYONLY)

add_executable(simple-test "test.cpp")

include_directories(simple-test ${PROJ_INCLUDE_PATH})

target_link_libraries(simple-test param-lib)

add_subdirectory(opengl-sample)

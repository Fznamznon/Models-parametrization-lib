cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function (get_all_files
  sourceListOut
  rootPath
  regex
  # ARGV3 recursion = TRUE
)
  set(globList GLOB_RECURSE)
  if((${ARGC} GREATER 3) AND ("${ARGV3}" STREQUAL "FALSE"))
    set(globList GLOB)
  endif()
  file(
    ${globList} sourceListLocal
    LIST_DIRECTORIES false
    "${rootPath}/${regex}"
  )
  set(${sourceListOut} ${sourceListLocal} PARENT_SCOPE)
endfunction (get_all_files)

set(sourceRootPath "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(includeRootPath "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(PROJ_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

get_all_files(sourceList "${sourceRootPath}" "*.cpp")
get_all_files(headerList "${includeRootPath}" "*.h")

add_library(param-lib
  "${sourceList}"
  "${headerList}"
)

include_directories(param-lib "${includeRootPath}")

# Install
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE)
set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY TRUE)
install(TARGETS param-lib DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
DESTINATION .)

add_subdirectory(tests)

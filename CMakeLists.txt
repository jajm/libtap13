cmake_minimum_required (VERSION 2.8.2)
project (libtap13)

find_package (PkgConfig)
pkg_check_modules (YAML REQUIRED yaml-0.1)

include_directories (include)

add_compile_options(-g -Wall -Wextra -Werror -std=c11)

add_subdirectory (src)
add_subdirectory (t)
add_subdirectory (examples)
add_subdirectory (include)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
  @ONLY
)

install (FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION lib/pkgconfig)

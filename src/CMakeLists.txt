add_library(libtap13 SHARED tap.c)
target_link_libraries (libtap13 ${YAML_LIBRARIES})

set_property(TARGET libtap13 PROPERTY OUTPUT_NAME tap13)

install (TARGETS libtap13 DESTINATION lib)

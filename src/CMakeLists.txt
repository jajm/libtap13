add_library(libtap13 SHARED tap.c)
target_link_libraries (libtap13 ${YAML_LIBRARIES})

set_target_properties (libtap13 PROPERTIES
    OUTPUT_NAME tap13
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

install (TARGETS libtap13 DESTINATION lib)

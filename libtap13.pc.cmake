prefix=@CMAKE_INSTALL_PREFIX@
includedir=${prefix}/include/@PROJECT_NAME@
libdir=${prefix}/lib

Name: @PROJECT_NAME@
Description: C library to produce TAP13 output
Version: @PROJECT_VERSION@
Requires.private: yaml-0.1
Libs: -L${libdir} -ltap13
Cflags: -I${includedir}

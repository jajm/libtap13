prefix=@CMAKE_INSTALL_PREFIX@
includedir=${prefix}/include
libdir=${prefix}/lib

Name: @PROJECT_NAME@
Description: @PROJECT_DESCRIPTION@
Version: @PROJECT_VERSION@
Requires.private: yaml-0.1
Libs: -L${libdir} -ltap13
Cflags: -I${includedir}

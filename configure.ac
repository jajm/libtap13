AC_INIT([libtap13], [0.1], [jajm@jajm.org])

LIBTOOL_CURRENT=0
LIBTOOL_REVISION=0
LIBTOOL_AGE=0
AC_SUBST(LIBTOOL_CURRENT)
AC_SUBST(LIBTOOL_REVISION)
AC_SUBST(LIBTOOL_AGE)

AC_CHECK_HEADER([yaml.h], , AC_MSG_ERROR([yaml.h not found]))
AC_CHECK_LIB([yaml], [yaml_parser_load], , AC_MSG_ERROR([required library yaml not found]))

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	include/Makefile
	examples/Makefile
	libtap13.pc
	config.mk
])

AC_OUTPUT

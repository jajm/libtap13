AC_PREREQ([2.69])
LT_PREREQ([2.4.2])

AC_INIT([libtap13], [1.0.1], [jajm@jajm.org])
LT_INIT()

AC_SUBST(LIBTOOL_CURRENT, 0)
AC_SUBST(LIBTOOL_REVISION, 0)
AC_SUBST(LIBTOOL_AGE, 0)

AC_PROG_CC
AC_CHECK_HEADERS([stdlib.h string.h stdio.h stdarg.h])

PKG_CHECK_MODULES(YAML, [yaml-0.1])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	include/Makefile
	examples/Makefile
	libtap13.pc
	config.mk
])

AC_OUTPUT

AC_PREREQ([2.63])
AC_INIT([Gnoomle], [0.1], [lerks@users.sourceforge.net], [gnoomle])
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/interface.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 po/Makefile
 src/Makefile
])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AM_PROG_LIBTOOL
PKG_CHECK_MODULES(GNOOMLE, [
 gtkmm-2.4 >= 2.8
 libxml++-2.6
])

# Checks for header files.
AC_CHECK_HEADERS([libintl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt])

AC_OUTPUT

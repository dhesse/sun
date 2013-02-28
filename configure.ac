#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([SUN], [0.0], [herr.dirk.hesse@gmail.com])
AM_INIT_AUTOMAKE()
LT_INIT
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_ARG_WITH([gtest-srcdir], [AS_HELP_STRING([--with-gtest-srcdir=DIR],
 [Path to Googletest.])], [], [])
AC_SUBST([GTEST_DIR],["$with_gtest_srcdir"])


AC_OUTPUT(Makefile testing/Makefile)

AC_OUTPUT

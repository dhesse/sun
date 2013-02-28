AUTOMAKE_OPTIONS = foreign
AM_CPPFLAGS = -I${GTEST_DIR}/include -I${GTEST_DIR} -I..\
	-I${top_srcdir} -I${top_srcdir}/include 
lib_LTLIBRARIES = lib/libgtest.la lib/libgtest_main.la
lib_libgtest_la_SOURCES = ${GTEST_DIR}/src/gtest-all.cc
lib_libgtest_main_la_SOURCES = ${GTEST_DIR}/src/gtest_main.cc
lib_libgtest_main_la_LIBADD = lib/libgtest.la

LDADD = lib/libgtest_main.la

bin_PROGRAMS = Arithmetic

Arithmetic_SOURCES = Arithmetic.cc

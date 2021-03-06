AC_INIT([mike], [0.0.1], [chris@nu7hat.ch])

# Base configuration.

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-m4])
AC_CONFIG_SRCDIR([src/])

# Check for compiler.

AC_PROG_CXX
AC_PROG_LIBTOOL
AM_PROG_CC_C_O
AC_LANG_CPLUSPLUS

# Extra arguments for specifying which v8 installation use.

AC_ARG_WITH([v8],
	AC_HELP_STRING([--with-v8=<path>], [Path to V8's directory.]),
	v8dir=$withval, v8dir=[/usr/lib/v8])

AC_MSG_CHECKING([for v8 engine])

LDFLAGS="-L$v8dir $LDFLAGS"
CPPFLAGS="-I$v8dir/include $CPPFLAGS"

AC_MSG_RESULT([$v8dir])

AC_CHECK_LIB([v8], [main], [LIBV8=-lv8], AC_MSG_ERROR([this package requires v8.]))
AC_CHECK_HEADERS([v8.h v8-debug.h], [], AC_MSG_ERROR([this package requires v8's header files.]), AC_INCLUDES_DEFAULT)

AC_SUBST([LIVB8])

# Checking for libxml2.

AC_ARG_WITH([xml2],
	AC_HELP_STRING([--with-xml2=<path>], [Path to libXML2's include dir.]),
	xml2_include=$withval, xml2_include=[/usr/include/libxml2])

CPPFLAGS="-I$xml2_include $CPPFLAGS"
	
AC_CHECK_LIB([xml2], [main], [LIBXML2=-lxml2], [AC_MSG_ERROR(this package requires xml2.)])
AC_CHECK_HEADER([libxml/tree.h], [], [AC_MSG_ERROR(this package requires libxml/tree.h)])

AC_SUBST([LIBXML2])

# Init Automage with following options. 

AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Werror])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Check for programs.

AC_CHECK_PROGS([FIND], [find], [:])
AC_CHECK_PROGS([SCONS], [scons], [:])

# Check for CppUnit. 

ifdef([AM_PATH_CPPUNIT], [AM_PATH_CPPUNIT()], [])

AC_CHECK_LIB([cppunit], [main], [cppunit=yes], [cppunit=no])
AC_MSG_CHECKING([whether unit tests are available])

if test x$cppunit=xyes; then
   AC_MSG_RESULT([yes])
else
   AC_MSG_RESULT([no, unit tests disabled])
fi

if test "$CPPUNIT_LIBS"="x"; then
   CPPUNIT_LIBS="-lcppunit"
   AC_SUBST([CPPUNIT_LIBS])
fi

AM_CONDITIONAL(HAVE_CPPUNIT, [test x$cppunit=xyes])

# Check for required libraries.

AC_CHECK_LIB([pthread], [main], [LIBPTHREAD=-lpthread], [AC_MSG_ERROR(this package requires pthread.)])
AC_CHECK_LIB([curl], [main], [LIBCURL=-lcurl], [AC_MSG_ERROR(this package requires curl.)])
AC_CHECK_LIB([uuid], [main], [LIBUUID=-luuid], [AC_MSG_ERROR(this package requires uuid.)])

AC_SUBST([LIBPTHREAD])
AC_SUBST([LIBCURL])
AC_SUBST([LIBUUID])

# Check for headers. 

AC_CHECK_HEADER([unistd.h], [], [AC_MSG_ERROR(this package requires unistd.h)])
AC_CHECK_HEADER([sys/param.h], [], [AC_MSG_ERROR(this package requires sys/param.h)])
AC_CHECK_HEADER([uuid/uuid.h], [], [AC_MSG_ERROR(this package requires uuid/uuid.h)])

# Config header.

AC_CONFIG_HEADERS([src/Config.h])

# Package settings.

MIKE_LIB_NAME=mike
MIKE_LIB_VERSION=0.0.1 # update version no. in src/mike.h after version bump
MIKE_LIB_VERSION_INFO=0:0:0
MIKE_LIB_RELEASE=1
MIKE_LIBS="$LIBV8 $LIBCURL $LIBXML2 $LIBPTHREAD $LIBUUID"

AC_SUBST([MIKE_LIB_NAME])
AC_SUBST([MIKE_LIB_VERSION])
AC_SUBST([MIKE_LIB_VERSION_INFO])
AC_SUBST([MIKE_LIB_RELEASE])
AC_SUBST([MIKE_LIBS])

# Update linker and compiler flags.

CPPFLAGS="-fPIC $CPPFLAGS"
LDFLAGS="$MIKE_LIBS $LDFLAGS"

# Specify makefiles. 

AC_CONFIG_FILES(Makefile)

# Generate output. 

AC_OUTPUT
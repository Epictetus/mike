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
	v8dir=$withval, v8dir=[:])

AC_MSG_CHECKING([for v8 engine])

if test x$v8dir = x:; then
   v8dir=[$(pwd)/deps/v8]

#   LDFLAGS="-L$v8dir/lib $LDFLAGS"
#   CPPFLAGS="-I$v8dir/include $CPPFLAGS"
#   LIBV8=-lv8

   AC_MSG_RESULT([$v8dir])
else
#   LDFLAGS="-L$v8dir/lib $LDFLAGS"
#   CPPFLAGS="-I$v8dir/include $CPPFLAGS"

   AC_MSG_RESULT([$v8dir])
   
   AC_CHECK_LIB([v8], [main], [LIBV8=-lv8], AC_MSG_ERROR([this package requires v8.]))
   AC_CHECK_HEADERS([v8.h v8-debug.h], [], AC_MSG_ERROR([this package requires v8's header files.]), AC_INCLUDES_DEFAULT)
fi

AC_SUBST([LIVB8])

# Checking for libxml2.

AC_ARG_WITH([xml2],
	AC_HELP_STRING([--with-xml2=<path>], [Path to libXML2's include dir.]),
	xml2_include=$withval, xml2_include=/usr/include/libxml2)

CPPFLAGS="-I$xml2_include $CPPFLAGS"
	
AC_CHECK_LIB([xml2], [main], [LIBXML2=-lxml2], [AC_MSG_ERROR(this package requires xml2.)])
AC_CHECK_HEADER([libxml/tree.h], [], [AC_MSG_ERROR(this package requires libxml/tree.h)])

AC_SUBST([LIBXML2])

# Checking for libmagic

AC_ARG_WITH([magic],
	AC_HELP_STRING([--with-magic=<path>], [Path to libmagic's intall dir.]),
	magic_dir=$withval, magic_dir=/usr)

CPPFLAGS="-I$magic_dir/include $CPPFLAGS"
LDFLAGS="-I$magic_dir/lib $CPPFLAGS"

AC_CHECK_LIB([magic], [magic_open], [LIBMAGIC=-lmagic], [AC_MSG_ERROR(this package requires magic.)])
AC_CHECK_HEADER([magic.h], [], [AC_MSG_ERROR(this package requires magic.h)])

AC_SUBST([LIBMAGIC])

# Init Automage with following options. 

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Check for programs.

AC_CHECK_PROGS([FIND], [find], [:])
AC_CHECK_PROGS([SCONS], [scons], [:])

# Check for CppUnit. 

ifdef([AM_PATH_CPPUNIT], [AM_PATH_CPPUNIT()], [])

AC_CHECK_LIB([cppunit], [main], [cppunit=yes], [cppunit=no])
AC_MSG_CHECKING([whether unit tests are available])

if test x$cppunit = xyes; then
   AC_MSG_RESULT([yes])
else
   AC_MSG_RESULT([no, unit tests disabled])
fi

AM_CONDITIONAL(HAVE_CPPUNIT, [test x$cppunit = xyes])

# Check for required libraries.

AC_CHECK_LIB([pthread], [main], [LIBPTHREAD=-lpthread], [AC_MSG_ERROR(this package requires pthread.)])
AC_CHECK_LIB([curl], [main], [LIBCURL=-lcurl], [AC_MSG_ERROR(this package requires curl.)])

AC_SUBST([LIBPTHREAD])
AC_SUBST([LIBCURL])

# Check for headers. 

AC_CHECK_HEADER([unistd.h], [], [AC_MSG_ERROR(this package requires unistd.h)])
AC_CHECK_HEADER([sys/param.h], [], [AC_MSG_ERROR(this package requires sys/param.h)])

# Config header.

AC_CONFIG_HEADERS([config.h])

# Package settings.

MIKE_LIB_NAME=mike
MIKE_LIB_VERSION=0.0.1 # update version no. in src/mike.h after version bump
MIKE_LIB_VERSION_INFO=0:0:0
MIKE_LIB_RELEASE=1
MIKE_LIBS="$LIBV8 $LIBCURL $LIBXML2 $LIBPTHREAD $LIBMAGIC"

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
AC_CONFIG_FILES(src/Makefile)

if test x$cppunit = xyes; then
   AC_CONFIG_FILES(test/Makefile)
fi

# Generate output. 

AC_OUTPUT
AC_INIT([mike], [0.0.1], [chris@nu7hat.ch])

# Base configuration.

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-m4])
AC_CONFIG_SRCDIR([src/])

# Check for compiler.

AC_PROG_CXX
AC_PROG_LIBTOOL
AC_LANG_CPLUSPLUS

# Check architecture (for v8), and initialize automake.

AM_CONDITIONAL(CPU_IS_X64, [test `uname -m` = x86_64])

if test "$CPU_IS_X64" = 0; then
   V8_ARCH=ia32
else
   V8_ARCH=x64
fi

# Additional v8 settings.

V8_DIR=deps/v8
V8_MODE=release
V8_SNAPSHOT=off
V8_LIBRARY=static
V8_CCFLAGS="-fPIC -fno-builtin-memcpy"

AC_SUBST([V8_DIR])
AC_SUBST([V8_ARCH])
AC_SUBST([V8_MODE])
AC_SUBST([V8_SNAPSHOT])
AC_SUBST([V8_LIBRARY])
AC_SUBST([V8_CCFLAGS])

# Check for scons (required to compile v8)

AC_CHECK_PROGS([FIND], [find], [:])
AC_CHECK_PROGS([SCONS], [scons], [:])
AC_CHECK_PROGS([COFFEE], [coffee], [:])

if test "$SCONS" = :; then
   AC_MSG_ERROR([this package needs scons.])
fi

if test "$COFFEE" = :; then
   AC_MSG_ERROR([this package needs coffee.])
fi

# Check for CppUnit. 

ifdef([AM_PATH_CPPUNIT], [AM_PATH_CPPUNIT()], [])

# Init Automage with following options. 

AM_INIT_AUTOMAKE([foreign color-tests -Wall -Werror])

# Check for required libraries.

AC_CHECK_LIB([pthread], [main], [LIBPTHREAD=-lpthread], [AC_MSG_ERROR(this package requires pthread.)])
AC_CHECK_LIB([curl], [main], [LIBCURL=-lcurl], [AC_MSG_ERROR(this package requires curl.)])
AC_CHECK_LIB([pcre], [main], [LIBPCRE=-lpcre], [AC_MSG_ERROR(this package requires pcre.)])

LIBV8=-lv8

AC_SUBST([LIBV8])
AC_SUBST([LIBCURL])
AC_SUBST([LIBPCRE])
AC_SUBST([LIBPTHREAD])

# Check for headers. 

AC_CHECK_HEADERS([string string.h stdio.h stdlib.h curl/curl.h])
AC_CONFIG_HEADERS([config.h])

# Package settings.

MIKE_LIB_NAME=mike
MIKE_LIB_VERSION=0.0.1 # update version no. in src/mike.h after version bump
MIKE_LIB_VERSION_INFO=0:0:0
MIKE_LIB_RELEASE=1
MIKE_LIBS="$LIBPCRE $LIBCURL $LIBPTHREAD"

AC_SUBST([MIKE_LIB_NAME])
AC_SUBST([MIKE_LIB_VERSION])
AC_SUBST([MIKE_LIB_VERSION_INFO])
AC_SUBST([MIKE_LIB_RELEASE])
AC_SUBST([MIKE_LIBS])

# Specify makefiles. 

AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(src/Makefile)
AC_CONFIG_FILES(src/browser/Makefile)
AC_CONFIG_FILES(test/Makefile)

# Generate output. 

AC_OUTPUT
# C++ source files.

cc_sources = \
	mike/script.cc \
	mike/stdio.cc \
	mike/env.cc \
	mike.cc

# Header files. 

h_sources = \
	mike/script.h \
	mike/stdio.h \
	mike/env.h \
	mike.h

# Local include paths for compiler.

cxx_includes = \
	-I$(srcdir)/../deps/v8/include

# Local libs for linker. 

ld_libs = \
	$(srcdir)/../deps/v8/libv8.a

# Mike library configuration. 

lib_LTLIBRARIES = libmike.la
include_HEADERS = mike.h
libmike_la_SOURCES = $(h_sources) $(cc_sources)
libmike_la_CXXFLAGS = $(cxx_includes) -fPIC
libmike_la_LDFLAGS = $(ld_libs) $(MIKE_LIBS) -release $(MIKE_RELEASE) -version-info $(MIKE_VERSION_INFO)

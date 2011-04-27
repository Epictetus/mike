# C++ source files.

cc_sources = \
	cctest/cctest.cc

# Local include paths for compiler. 

cxx_includes = \
	-I$(srcdir)/../src/ \
	-I$(srcdir)/../deps/v8/include

# Local libraries for linker.

ld_libs = \
	$(srcdir)/../deps/v8/libv8.a \
	$(srcdir)/../src/libmike.la

# Cpp code test suite config. 

UNITTESTS = cctest/cctest
TESTS = $(UNITTESTS)

check_PROGRAMS = $(UNITTESTS)
noinst_PROGRAMS = $(UNITTESTS)
cctest_cctest_SOURCES = $(cc_sources)
cctest_cctest_CXXFLAGS = $(cxx_includes) -fPIC
cctest_cctest_LDFLAGS = $(ld_libs) -lcppunit

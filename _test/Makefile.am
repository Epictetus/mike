# Local libraries for linker.

ld_libs = \
	$(srcdir)/../deps/v8/libv8.a \
	$(srcdir)/../src/libmike.la

# Local include paths for compiler. 

cctest_cxx_includes = \
	-I$(srcdir)/../src/ \
	-I$(srcdir)/../deps/v8/include

# C++ code tests source files.

cctest_cc_sources = \
	cctest/cctest.cc

# JS code tests source files.

jstest_cc_sources = \
	jstest/jstest.cc

# Test suites configuration. 

UNITTESTS = cctest/cctest jstest/jstest
TESTS = $(UNITTESTS)

check_PROGRAMS = $(UNITTESTS)
noinst_PROGRAMS = $(UNITTESTS)

cctest_cctest_SOURCES = $(cctest_cc_sources)
cctest_cctest_CXXFLAGS = $(cctest_cxx_includes) -fPIC
cctest_cctest_LDFLAGS = $(ld_libs) -lcppunit

jstest_jstest_SOURCES = $(jstest_cc_sources)
jstest_jstest_CXXFLAGS = $(jstest_cxx_includes) -fPIC
jstest_jstest_LDFLAGS = $(ld_libs) -lcppunit

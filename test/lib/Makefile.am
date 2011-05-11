testeedir = $(srcdir)/../../src
v8dir = $(srcdir)/../../deps/v8

source_files = \
	$(testeedir)/test/macros.h \
	$(testeedir)/lib/src/file.h \
	$(testeedir)/lib/src/lib.h \
	$(testeedir)/lib/src/file.cc \
	$(testeedir)/lib/src/lib.cc

test_files = \
	file_test.cc \
	main.cc

cxx_includes = \
	-I$(v8dir)/include \
	-I$(testeedir)

ld_libs = \
	$(v8dir)/libv8.a

suite_SOURCES = $(source_files) $(test_files)
suite_CXXFLAGS = $(cxx_includes) -fPIC
suite_LDFLAGS = $(ld_libs) -lcppunit

check_PROGRAMS = suite
noinst_PROGRAMS = suite

suite = lib_suite
testeedir = $(srcdir)/../../src
v8dir = $(srcdir)/../../deps/v8

source_files = \
	$(testeedir)/test/macros.h \
	$(testeedir)/lib/glue/file.h \
	$(testeedir)/lib/glue/glue.h \
	$(testeedir)/lib/glue/file.cc \
	$(testeedir)/lib/glue/glue.cc

test_files = \
	file_test.cc \
	main.cc

cxx_includes = \
	-I$(v8dir)/include \
	-I$(testeedir)

ld_libs = \
	$(v8dir)/libv8.a

lib_suite_SOURCES = $(source_files) $(test_files)
lib_suite_CXXFLAGS = $(cxx_includes) -fPIC
lib_suite_LDFLAGS = $(ld_libs) -lcppunit -lpthread

check_PROGRAMS = $(suite)
noinst_PROGRAMS = $(suite)

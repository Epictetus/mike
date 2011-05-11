suite = core_suite
testeedir = $(srcdir)/../../src
v8dir = $(srcdir)/../../deps/v8

source_files = \
	$(testeedir)/test/macros.h \
	$(testeedir)/core/script.h \
	$(testeedir)/core/script.cc

test_files = \
	script_test.cc \
	main.cc

cxx_includes = \
	-I$(v8dir)/include \
	-I$(testeedir)

ld_libs = \
	$(v8dir)/libv8.a

core_suite_SOURCES = $(source_files) $(test_files)
core_suite_CXXFLAGS = $(cxx_includes) -fPIC
core_suite_LDFLAGS = $(ld_libs) -lcppunit -lpthread

check_PROGRAMS = $(suite)
noinst_PROGRAMS = $(suite)

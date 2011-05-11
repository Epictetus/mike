suite = core_suite
testeedir = $(srcdir)/../../src
v8dir = $(srcdir)/../../deps/v8

source_files = \
	$(testeedir)/test/macros.h \
	$(testeedir)/glue/file.h \
	$(testeedir)/glue/system.h \
	$(testeedir)/glue/io.h \
	$(testeedir)/glue/glue.h \
	$(testeedir)/glue/file.cc \
	$(testeedir)/glue/system.cc \
	$(testeedir)/glue/io.cc \
	$(testeedir)/glue/glue.cc \
	$(testeedir)/core/script.h \
	$(testeedir)/core/context.h \
	$(testeedir)/core/script.cc \
	$(testeedir)/core/context.cc

test_files = \
	test_script.cc \
	test_context.cc \
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

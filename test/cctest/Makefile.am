suite = cc_suite
testeedir = $(srcdir)/../../src
v8dir = $(srcdir)/../../deps/v8
mikelibdir = -DMIKE_LIBDIR="\"`pwd`/../../lib\""

source_files = \
	$(testeedir)/test/helpers.h \
	$(testeedir)/test/helpers.cc \
	$(testeedir)/glue/file.h \
	$(testeedir)/glue/system.h \
	$(testeedir)/glue/stdio.h \
	$(testeedir)/glue/glue.h \
	$(testeedir)/glue/file.cc \
	$(testeedir)/glue/system.cc \
	$(testeedir)/glue/stdio.cc \
	$(testeedir)/glue/glue.cc \
	$(testeedir)/core/script.h \
	$(testeedir)/core/context.h \
	$(testeedir)/core/script.cc \
	$(testeedir)/core/context.cc

test_files = \
	test_context.cc \
	main.cc

cxx_includes = \
	-I$(v8dir)/include \
	-I$(testeedir)

ld_libs = \
	$(v8dir)/libv8.a

cc_suite_SOURCES = $(source_files) $(test_files)
cc_suite_CXXFLAGS = $(cxx_includes) $(mikelibdir) -fPIC
cc_suite_LDFLAGS = $(ld_libs) -lcppunit -lpthread

check_PROGRAMS = $(suite)
noinst_PROGRAMS = $(suite)

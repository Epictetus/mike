SUBDIRS = src

if HAVE_CPPUNIT 
   SUBDIRS += test
endif

deps/v8:
	@echo "Making V8 engine in deps/v8"
	-cd $(V8_DIR) && CCFLAGS="$(V8_CCFLAGS)" $(SCONS) mode=$(V8_MODE) snapshot=$(V8_SNAPSHOT) library=$(V8_LIBRARY) arch=$(V8_ARCH)
all: deps/v8

.PHONY: deps/v8
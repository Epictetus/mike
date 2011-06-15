SUBDIRS = src

if HAVE_CPPUNIT 
   SUBDIRS += test
endif

deps-v8:
	@echo "Making V8 engine in deps/v8"
	cd $(V8_DIR) && CCFLAGS="$(V8_CCFLAGS)" $(SCONS) mode=$(V8_MODE) snapshot=$(V8_SNAPSHOT) library=$(V8_LIBRARY) arch=$(V8_ARCH)
	mkdir -p $(V8_DIR)/lib && cp $(V8_DIR)/libv8.a $(V8_DIR)/lib/

tmp-dir:
	mkdir -p tmp

stop-dummy-app:
	[ -f tmp/dummy_app.pid ] && kill `cat tmp/dummy_app.pid` &>/dev/null || true
	rm -f tmp/dummy_app.pid

start-dummy-app: tmp-dir stop-dummy-app
	@echo "Starting dummy web application"
	ruby test/fixtures/dummy_app.rb &>/dev/null & echo $$! >tmp/dummy_app.pid; sleep 1

test: start-dummy-app check
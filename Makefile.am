SUBDIRS = src

if HAVE_CPPUNIT 
   SUBDIRS += test
endif

V8DIR = deps/v8
V8LIBTYPE = static
V8MODE = release
V8SNAPSHOT = off

v8:
	@echo "Compiling v8 in deps/v8"
	mkdir -p $(V8DIR)/lib
	arch=`./tools/arch-detect.sh` && cd $(V8DIR) && scons library=$(V8LIBTYPE) mode=$(V8MODE) snapshot=$(V8SNAPSHOT) arch=$$arch
	cp $(V8DIR)/*.{a,so} $(V8DIR)/lib/ &>/dev/null || true

tmp-dir:
	mkdir -p tmp

stop-dummy-app:
	[ -f tmp/dummy_app.pid ] && kill `cat tmp/dummy_app.pid` &>/dev/null || true
	rm -f tmp/dummy_app.pid

start-dummy-app: tmp-dir stop-dummy-app
	@echo "Starting dummy web application"
	nohup ruby test/fixtures/dummy_app.rb &>tmp/dummy_app.log & echo $$! >tmp/dummy_app.pid && sleep 2

test: start-dummy-app check
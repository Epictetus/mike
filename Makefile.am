SUBDIRS = src

if HAVE_CPPUNIT 
   SUBDIRS += test
endif

tmp-dir:
	mkdir -p tmp

stop-dummy-app:
	[ -f tmp/dummy_app.pid ] && kill `cat tmp/dummy_app.pid` &>/dev/null || true
	rm -f tmp/dummy_app.pid

start-dummy-app: tmp-dir stop-dummy-app
	ruby test/fixtures/dummy_app.rb &>/dev/null & echo $$! >tmp/dummy_app.pid; sleep 1

check-all: start-dummy-app check
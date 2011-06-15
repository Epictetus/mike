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
	@echo "Starting dummy web application"
	nohup ruby test/fixtures/dummy_app.rb &>tmp/dummy_app.log & echo $$! >tmp/dummy_app.pid
	sleep 1

test: start-dummy-app check
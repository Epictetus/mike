SOURCE_FILES = \
	src/Page.cc \
	src/History.cc \
	src/Browser.cc \
	src/Window.cc \
	src/Frame.cc \
	src/utils/Helpers.cc \
	src/http/Response.cc \
	src/http/Request.cc \
	src/http/Headers.cc \
	src/xml/XmlElement.cc \
	src/xml/XmlPage.cc \
	src/html/HtmlPage.cc \
	src/html/HtmlAttrs.cc \
	src/html/HtmlElement.cc \
	src/html/HtmlAnchorElement.cc \
	src/html/HtmlEventHandler.cc \
	src/html/HtmlFrame.cc \
	src/javascript/JavaScriptHandler.cc \
	src/javascript/glue/Window.cc

# Build this part only if unit/integration testing is enabled.
if HAVE_CPPUNIT

TEST_FILES = \
	test/TestHttp.cc \
	test/TestPage.cc \
	test/TestXmlPage.cc \
	test/TestXmlElement.cc \
	test/TestHtmlPage.cc \
	test/TestHtmlElement.cc \
	test/TestHistory.cc \
	test/TestBrowser.cc \
	test/TestWindow.cc \
	test/TestUtils.cc \
	test/TestPector.cc \
	test/TestJavaScriptWindow.cc \
	test/Main.cc

# Don't install this program but run as test suite.
noinst_PROGRAMS = test-suite
check_PROGRAMS  = test-suite

test_suite_SOURCES = \
	$(SOURCE_FILES) \
	$(TEST_FILES)

test_suite_CPPFLAGS = -Isrc
test_suite_LDFLAGS  = -lcppunit

TESTS = test-suite

endif # HAVE_CPPUNIT

# Custom targets.

mkdir-tmp:
	mkdir -p tmp

stop-dummy-app:
	@echo "Stopping server with dummy application"
	[ -f tmp/dummy_app.pid ] && kill `cat tmp/dummy_app.pid` &>/dev/null || true
	rm -f tmp/dummy_app.pid

start-dummy-app: mkdir-tmp
	@echo "Starting server with dummy application"
	nohup ruby test/fixtures/dummy_app.rb &>tmp/dummy_app.log & echo $$! >tmp/dummy_app.pid

restart-dummy-app: stop-dummy-app start-dummy-app

test: restart-dummy-app check
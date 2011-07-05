# Test suite name.
SUITE = suite

# Path to tested sources and includes.
TESTEE_SOURCES_DIR = $(srcdir)/../src
TESTEE_INCLUDES_DIR = $(TESTEE_SOURCES_DIR)

# List of sources to compile and test.
TESTEE_FILES = \
	$(TESTEE_SOURCES_DIR)/utils/Helpers.cc \
	$(TESTEE_SOURCES_DIR)/http/Response.cc \
	$(TESTEE_SOURCES_DIR)/http/Request.cc \
	$(TESTEE_SOURCES_DIR)/http/Headers.cc \
	$(TESTEE_SOURCES_DIR)/Page.cc \
	$(TESTEE_SOURCES_DIR)/History.cc \
	$(TESTEE_SOURCES_DIR)/Browser.cc \
	$(TESTEE_SOURCES_DIR)/Window.cc \
	$(TESTEE_SOURCES_DIR)/Frame.cc \
	$(TESTEE_SOURCES_DIR)/xml/XmlElement.cc \
	$(TESTEE_SOURCES_DIR)/xml/XmlPage.cc \
	$(TESTEE_SOURCES_DIR)/html/HtmlPage.cc \
	$(TESTEE_SOURCES_DIR)/html/HtmlAttrs.cc \
	$(TESTEE_SOURCES_DIR)/html/HtmlElement.cc \
	$(TESTEE_SOURCES_DIR)/html/HtmlEventHandler.cc \
	$(TESTEE_SOURCES_DIR)/html/HtmlFrame.cc \
	$(TESTEE_SOURCES_DIR)/javascript/JavaScriptHandler.cc 

# List of test files.
TEST_FILES = \
	TestHttp.cc \
	TestPage.cc \
	TestXmlPage.cc \
	TestXmlElement.cc \
	TestHtmlPage.cc \
	TestHtmlElement.cc \
	TestHistory.cc \
	TestBrowser.cc \
	TestWindow.cc \
	TestUtils.cc \
	TestPector.cc \
	Main.cc

# Test suite setting and compiler flags.
suite_SOURCES = \
	$(TESTEE_FILES) \
	$(TEST_FILES)

suite_CPPFLAGS = \
	-I$(TESTEE_INCLUDES_DIR)

suite_LDFLAGS = -lcppunit

# Register this test suite. 
check_PROGRAMS = $(SUITE)
noinst_PROGRAMS = $(SUITE)

# Test suites to execute.
TESTS = suite
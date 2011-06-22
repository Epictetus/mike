# Test suite name.
SUITE = suite

# Path to tested sources and includes.
TESTEE_SOURCES_DIR = $(srcdir)/../src
TESTEE_INCLUDES_DIR = $(TESTEE_SOURCES_DIR)

# List of sources to compile and test.
TESTEE_FILES = \
	$(TESTEE_SOURCES_DIR)/utils/CppunitMacros.h \
	$(TESTEE_SOURCES_DIR)/utils/SystemInfo.h \
	$(TESTEE_SOURCES_DIR)/utils/Helpers.h \
	$(TESTEE_SOURCES_DIR)/utils/Helpers.cc \
	$(TESTEE_SOURCES_DIR)/http/Response.h \
	$(TESTEE_SOURCES_DIR)/http/Response.cc \
	$(TESTEE_SOURCES_DIR)/http/Request.h \
	$(TESTEE_SOURCES_DIR)/http/Request.cc \
	$(TESTEE_SOURCES_DIR)/http/Headers.h \
	$(TESTEE_SOURCES_DIR)/http/Headers.cc \
	$(TESTEE_SOURCES_DIR)/Page.h \
	$(TESTEE_SOURCES_DIR)/Page.cc \
	$(TESTEE_SOURCES_DIR)/RegularPage.h \
	$(TESTEE_SOURCES_DIR)/RegularPage.cc \
	$(TESTEE_SOURCES_DIR)/History.h \
	$(TESTEE_SOURCES_DIR)/History.cc \
	$(TESTEE_SOURCES_DIR)/Browser.h \
	$(TESTEE_SOURCES_DIR)/Browser.cc \
	$(TESTEE_SOURCES_DIR)/BrowserWindow.h \
	$(TESTEE_SOURCES_DIR)/BrowserWindow.cc \
	$(TESTEE_SOURCES_DIR)/BrowserFrame.h \
	$(TESTEE_SOURCES_DIR)/BrowserFrame.cc \
	$(TESTEE_SOURCES_DIR)/xml/XmlElement.h \
	$(TESTEE_SOURCES_DIR)/xml/XmlElement.cc \
	$(TESTEE_SOURCES_DIR)/xml/XmlPage.h \
	$(TESTEE_SOURCES_DIR)/xml/XmlPage.cc \
	$(TESTEE_SOURCES_DIR)/html/HtmlPage.h \
	$(TESTEE_SOURCES_DIR)/html/HtmlPage.cc

# List of test files.
TEST_FILES = \
	TestHttp.cc \
	TestPage.cc \
	TestXmlPage.cc \
	TestXmlElement.cc \
	TestHtmlPage.cc \
	TestRegularPage.cc \
	TestHistory.cc \
	TestBrowser.cc \
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
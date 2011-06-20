# Test suite name.
SUITE = ccsuite

# Path to tested sources and includes.
TESTEE_SOURCES_DIR = $(srcdir)/../src
TESTEE_INCLUDES_DIR = $(TESTEE_SOURCES_DIR)

# List of sources to compile and test.
TESTEE_FILES = \
	$(TESTEE_SOURCES_DIR)/mike/utils/test_macros.h \
	$(TESTEE_SOURCES_DIR)/http/response.h \
	$(TESTEE_SOURCES_DIR)/http/response.cc \
	$(TESTEE_SOURCES_DIR)/http/request.h \
	$(TESTEE_SOURCES_DIR)/http/request.cc \
	$(TESTEE_SOURCES_DIR)/http/headers.h \
	$(TESTEE_SOURCES_DIR)/http/headers.cc \
	$(TESTEE_SOURCES_DIR)/page.h \
	$(TESTEE_SOURCES_DIR)/page.cc \
	$(TESTEE_SOURCES_DIR)/xml/xml_element.h \
	$(TESTEE_SOURCES_DIR)/xml/xml_element.cc \
	$(TESTEE_SOURCES_DIR)/xml/xml_element_set.h \
	$(TESTEE_SOURCES_DIR)/xml/xml_element_set.cc \
	$(TESTEE_SOURCES_DIR)/xml/xml_page.h \
	$(TESTEE_SOURCES_DIR)/xml/xml_page.cc \
	$(TESTEE_SOURCES_DIR)/html/html_page.h \
	$(TESTEE_SOURCES_DIR)/html/html_page.cc \
	$(TESTEE_SOURCES_DIR)/mike/utils/fs.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/fs.cc \
	$(TESTEE_SOURCES_DIR)/mike/utils/string.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/string.cc

# List of test files.
TEST_FILES = \
	test_http.cc \
	test_page.cc \
	main.cc

# Test suite setting and compiler flags.
ccsuite_SOURCES = \
	$(TESTEE_FILES) \
	$(TEST_FILES)

ccsuite_CPPFLAGS = \
	-I$(TESTEE_INCLUDES_DIR)

ccsuite_LDFLAGS = -lcppunit

# Register this test suite. 
check_PROGRAMS = $(SUITE)
noinst_PROGRAMS = $(SUITE)

# Test suites to execute.
TESTS = ccsuite
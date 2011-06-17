# Test suite name.
SUITE = ccsuite

# Path to tested sources and includes.
TESTEE_SOURCES_DIR = $(srcdir)/../../src
TESTEE_INCLUDES_DIR = $(TESTEE_SOURCES_DIR)

# List of sources to compile and test.
TESTEE_FILES = \
	$(TESTEE_SOURCES_DIR)/mike/utils/test_macros.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/http.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/http.cc \
	$(TESTEE_SOURCES_DIR)/mike/utils/fs.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/fs.cc \
	$(TESTEE_SOURCES_DIR)/mike/utils/string.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/string.cc

# List of test files.
TEST_FILES = \
	test_utils_http.cc \
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

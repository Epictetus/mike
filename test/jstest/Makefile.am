# Test suite name.
SUITE = jssuite

# Path to tested sources and includes.
TESTEE_SOURCES_DIR = $(srcdir)/../../src
TESTEE_INCLUDES_DIR = $(TESTEE_SOURCES_DIR)

# List of sources to compile and test.
TESTEE_FILES = \
	$(TESTEE_SOURCES_DIR)/mike/utils/http.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/http.cc \
	$(TESTEE_SOURCES_DIR)/mike/utils/fs.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/fs.cc \
	$(TESTEE_SOURCES_DIR)/mike/utils/string.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/string.cc \
	$(TESTEE_SOURCES_DIR)/mike/utils/test.h \
	$(TESTEE_SOURCES_DIR)/mike/utils/test.cc \
	$(TESTEE_SOURCES_DIR)/mike/config.h \
	$(TESTEE_SOURCES_DIR)/mike/window.h \
	$(TESTEE_SOURCES_DIR)/mike/window.cc \
	$(TESTEE_SOURCES_DIR)/mike/page.h \
	$(TESTEE_SOURCES_DIR)/mike/page.cc \
	$(TESTEE_SOURCES_DIR)/mike/frame.h \
	$(TESTEE_SOURCES_DIR)/mike/frame.cc \
	$(TESTEE_SOURCES_DIR)/mike/history.h \
	$(TESTEE_SOURCES_DIR)/mike/history.cc

# List of test files.
TEST_FILES = \
	main.cc

# Test suite setting and compiler flags.
jssuite_SOURCES = \
	$(TESTEE_FILES) \
	$(TEST_FILES)

jssuite_CPPFLAGS = \
	-I$(TESTEE_INCLUDES_DIR)

jssuite_LDFLAGS = -lcppunit

# Register this test suite. 
check_PROGRAMS = $(SUITE)
noinst_PROGRAMS = $(SUITE)

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "test/macros.h"
#include "core/context.h"

using namespace v8;
using namespace std;
using namespace mike;

class FileFunctionsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(FileFunctionsTest);
  CPPUNIT_TEST(existsFuncTest);
  CPPUNIT_TEST(isDirectoryFuncTest);
  CPPUNIT_TEST(isFileFuncTest);
  CPPUNIT_TEST(readFuncTest);
  CPPUNIT_TEST_SUITE_END();
private:
  context::Window *window;
public:
  void setUp();
  void tearDown();
protected:
  void existsFuncTest();
  void isDirectoryFuncTest();
  void isFileFuncTest();
  void readFuncTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FileFunctionsTest);

void FileFunctionsTest::setUp(void)
{
  window = context::New();
}

void FileFunctionsTest::tearDown(void)
{
  delete window;
}

void FileFunctionsTest::existsFuncTest()
{
  HandleScope scope;
  system("touch /tmp/test-exists");
  ASSERT_JS_EQUAL("File.exists('/tmp/test-exists')", True());
  ASSERT_JS_EQUAL("File.exists('/tmp/test-not-exists')", False());
  ASSERT_JS_EQUAL("File.exists()", Undefined());
}

void FileFunctionsTest::isDirectoryFuncTest()
{
  HandleScope scope;
  system("touch /tmp/test-file");
  system("mkdir -p /tmp/test-dir");
  ASSERT_JS_EQUAL("File.isDirectory('/tmp/test-file')", False());
  ASSERT_JS_EQUAL("File.isDirectory('/tmp/test-dir')", True());
  ASSERT_JS_EQUAL("File.isDirectory()", Undefined());
}

void FileFunctionsTest::isFileFuncTest()
{
  HandleScope scope;
  system("touch /tmp/test-file");
  system("mkdir -p /tmp/test-dir");
  ASSERT_JS_EQUAL("File.isFile('/tmp/test-file')", True());
  ASSERT_JS_EQUAL("File.isFile('/tmp/test-dir')", False());
  ASSERT_JS_EQUAL("File.isFile()", Undefined());
}

void FileFunctionsTest::readFuncTest()
{
  HandleScope scope;
  system("echo 'foobar' > /tmp/test-file");
  ASSERT_JS_EQUAL("File.read('/tmp/test-file')", String::New("foobar\n"));
  ASSERT_JS_EQUAL("File.read('/tmp/test-notexists')", Null());
  ASSERT_JS_EQUAL("File.read()", Undefined());
}

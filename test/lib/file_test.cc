#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "test/macros.h"
#include "lib/glue/file.h"

class FileFunctionsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(FileFunctionsTest);
  CPPUNIT_TEST(existsFuncTest);
  CPPUNIT_TEST_SUITE_END();
private:
  v8::Persistent<v8::Context> cxt;
public:
  void setUp();
  void tearDown();
protected:
  void existsFuncTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FileFunctionsTest);

void FileFunctionsTest::setUp(void)
{
  v8::HandleScope scope;
  cxt = v8::Context::New();
  cxt->Enter();
  cxt->Global()->Set(v8::String::NewSymbol("exists"), v8::FunctionTemplate::New(mike::glue::file::exists)->GetFunction());
}

void FileFunctionsTest::tearDown(void)
{
  cxt.Dispose();
}

void FileFunctionsTest::existsFuncTest()
{
  v8::HandleScope scope;
  system("touch /tmp/test-exists");
  ASSERT_V8_RESULT("exists('/tmp/test-exists')", v8::True());
  ASSERT_V8_RESULT("exists('/tmp/test-not-exists')", v8::False());
  ASSERT_V8_RESULT("exists()", v8::Null());
}

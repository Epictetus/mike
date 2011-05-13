#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "test/helpers.h"
#include "core/context.h"

using namespace v8;
using namespace std;
using namespace mike;

class IoFunctionsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(IoFunctionsTest);
  CPPUNIT_TEST(stdoutWriteFuncTest);
  CPPUNIT_TEST(stderrWriteFuncTest);
  CPPUNIT_TEST_SUITE_END();
private:
  context::Window *window;
public:
  void setUp();
  void tearDown();
protected:
  void stdoutWriteFuncTest();
  void stderrWriteFuncTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(IoFunctionsTest);

void IoFunctionsTest::setUp(void)
{
  window = context::New();
}

void IoFunctionsTest::tearDown(void)
{
  delete window;
}

void IoFunctionsTest::stdoutWriteFuncTest()
{
  HandleScope scope;
  ASSERT_JS_EQUAL("Stdout.write('.')", Null());
  ASSERT_JS_EQUAL("Stdout.write('.', '.')", Null());
}

void IoFunctionsTest::stderrWriteFuncTest()
{
  HandleScope scope;
  ASSERT_JS_EQUAL("Stderr.write('.')", Null());
  ASSERT_JS_EQUAL("Stderr.write('.', '.')", Null());
}

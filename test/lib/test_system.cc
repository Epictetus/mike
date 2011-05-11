#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <unistd.h>

#include "test/macros.h"
#include "core/context.h"

using namespace v8;
using namespace std;
using namespace mike;

class SystemFunctionsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(SystemFunctionsTest);
  CPPUNIT_TEST(pwdFuncTest);
  CPPUNIT_TEST_SUITE_END();
private:
  context::Window *window;
public:
  void setUp();
  void tearDown();
protected:
  void pwdFuncTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SystemFunctionsTest);

void SystemFunctionsTest::setUp(void)
{
  window = context::New();
}

void SystemFunctionsTest::tearDown(void)
{
  delete window;
}

void SystemFunctionsTest::pwdFuncTest()
{
  HandleScope scope;
  chdir("/tmp");
  ASSERT_EVAL("System.pwd()", String::New("/tmp"));
}

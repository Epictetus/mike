#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>

#include "test/macros.h"
#include "core/context.h"

using namespace v8;
using namespace std;
using namespace mike;

class SystemFunctionsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(SystemFunctionsTest);
  CPPUNIT_TEST(pwdFuncTest);
  CPPUNIT_TEST(cwdFuncTest);
  CPPUNIT_TEST_SUITE_END();
private:
  context::Window *window;
  string cwd;
public:
  void setUp();
  void tearDown();
protected:
  void pwdFuncTest();
  void cwdFuncTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SystemFunctionsTest);

void SystemFunctionsTest::setUp(void)
{
  window = context::New();
  char pcwd[MAXPATHLEN];
  getcwd(pcwd, MAXPATHLEN);
  cwd = string(pcwd) + "/../tmp";
  system(("mkdir -p " + cwd).c_str());
  chdir(cwd.c_str());
  getcwd(pcwd, MAXPATHLEN);
  cwd = string(pcwd);
}

void SystemFunctionsTest::tearDown(void)
{
  delete window;
}

void SystemFunctionsTest::pwdFuncTest()
{
  HandleScope scope;
  ASSERT_JS_EQUAL("System.pwd()", String::New(cwd.c_str()));
}

void SystemFunctionsTest::cwdFuncTest()
{
  HandleScope scope;
  system(("mkdir -p " + cwd + "/testing-dir").c_str());
  ASSERT_JS_EQUAL("System.cwd('not-exists')", False());
  ASSERT_JS_EQUAL("System.cwd('testing-dir')", True());
  ASSERT_JS_EQUAL("System.pwd()", String::New((cwd + "/testing-dir").c_str()));

}

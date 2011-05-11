#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "test/macros.h"
#include "core/context.h"

using namespace v8;
using namespace std;
using namespace mike;

class ConstantsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ConstantsTest);
  CPPUNIT_TEST(loadPathConstTest);
  CPPUNIT_TEST_SUITE_END();
private:
  context::Window *window;
public:
  void setUp();
  void tearDown();
protected:
  void loadPathConstTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ConstantsTest);

void ConstantsTest::setUp(void)
{
  window = context::New();
}

void ConstantsTest::tearDown(void)
{
  delete window;
}

void ConstantsTest::loadPathConstTest()
{
  HandleScope scope;
  ASSERT_JS_EQUAL("$LOAD_PATH", window->LoadPath());
  window->LoadPath()->Set(window->LoadPath()->Length(), String::New("."));
  ASSERT_JS_EQUAL("$LOAD_PATH[0] == '.';", True());
  window->Evaluate("$LOAD_PATH[1] = './lib';");
  ASSERT(window->LoadPath()->Get(1)->Equals(String::New("./lib")));
}

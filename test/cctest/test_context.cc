#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "test/helpers.h"
#include "core/context.h"

using namespace std;
using namespace v8;
using namespace mike;

class WindowContextTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(WindowContextTest);
  CPPUNIT_TEST(creatingAndEnteringContextTest);
  CPPUNIT_TEST(evaluateTest);
  CPPUNIT_TEST(loadPathTest);
  CPPUNIT_TEST_SUITE_END();
protected:
  void creatingAndEnteringContextTest();
  void evaluateTest();
  void loadPathTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(WindowContextTest);

void WindowContextTest::creatingAndEnteringContextTest()
{
  HandleScope scope;
  ASSERT(!Context::InContext());
  context::Window *window = context::New();
  ASSERT(Context::InContext());
  delete window;
}

void WindowContextTest::evaluateTest()
{
  HandleScope scope;
  context::Window *window = context::New();
  Handle<Value> result = window->Evaluate("var a=1; a;");
  ASSERT(!result.IsEmpty());
  ASSERT(result->Int32Value() == 1);
  delete window;
}

void WindowContextTest::loadPathTest()
{
  HandleScope scope;
  context::Window *window = context::New();
  ASSERT(window->LoadPath()->IsArray());
  delete window;
}

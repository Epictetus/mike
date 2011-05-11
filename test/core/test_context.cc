#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "test/macros.h"
#include "core/context.h"

using namespace std;
using namespace v8;
using namespace mike;

class WindowContextTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(WindowContextTest);
  CPPUNIT_TEST(creatingAndEnteringContextTest);
  CPPUNIT_TEST(evaluateTest);
  CPPUNIT_TEST(lastExecutedScriptTest);
  CPPUNIT_TEST(loadPathTest);
  CPPUNIT_TEST_SUITE_END();
protected:
  void creatingAndEnteringContextTest();
  void evaluateTest();
  void lastExecutedScriptTest();
  void loadPathTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(WindowContextTest);

void WindowContextTest::creatingAndEnteringContextTest()
{
  ASSERT(!Context::InContext());
  context::Window *window = context::New();
  Context::GetEntered()->Exit();
  window->EnterContext();
  ASSERT(Context::InContext());
  delete window;
}

void WindowContextTest::evaluateTest()
{
  context::Window *window = context::New();
  script::Info* info = window->Evaluate("var a=1; a;");
  ASSERT(info->result->Int32Value() == 1);
  ASSERT(info->name == "<eval>");
  ASSERT(info->source == "var a=1; a;");
  delete window;
}

void WindowContextTest::lastExecutedScriptTest()
{
  context::Window *window = context::New();
  script::Info *info = window->Evaluate("var a=1; a;");
  ASSERT(window->LastExecutedScript() == info);
  delete window;
}

void WindowContextTest::loadPathTest()
{
  context::Window *window = context::New();
  ASSERT(window->LoadPath()->IsArray());
  delete window;
}

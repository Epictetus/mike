#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "test/helpers.h"
#include "core/script.h"

using namespace std;
using namespace v8;
using namespace mike;

class ScriptTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ScriptTest);
  CPPUNIT_TEST(simpleRunTest);
  CPPUNIT_TEST(runWithRuntimeErrorTest);
  CPPUNIT_TEST(runWithCompileErrorTest);
  CPPUNIT_TEST_SUITE_END();
private:
  Persistent<Context> context;
public:
  void setUp();
  void tearDown();
protected:
  void simpleRunTest();
  void runWithRuntimeErrorTest();
  void runWithCompileErrorTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ScriptTest);

void ScriptTest::setUp(void)
{
  HandleScope scope;
  context = Context::New();
  context->Enter();
}

void ScriptTest::tearDown(void)
{
  context->Exit();
  context.Dispose();
}

void ScriptTest::simpleRunTest()
{
  string source = "var a=1; a;";
  string fname = "<test>";
  script::Info *info = script::Run(source, fname);
  ASSERT(info->source == source);
  ASSERT(info->name == fname);
  ASSERT(info->result->Int32Value() == 1);
  ASSERT(info->error == script::seNone);
  delete info;
}

void ScriptTest::runWithRuntimeErrorTest()
{
  script::Info *info = script::Run("foobar;", "<test>");
  ASSERT(info->result.IsEmpty());
  ASSERT(info->error == script::seRuntimeError);
  delete info;
}

void ScriptTest::runWithCompileErrorTest()
{
  script::Info *info = script::Run("dsfdf{dsfsd/sdf;", "<test>");
  ASSERT(info->result.IsEmpty());
  ASSERT(info->error == script::seCompileError);
  delete info;
}

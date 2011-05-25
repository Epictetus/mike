#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "mike/utils/test.h"

using namespace v8;
using namespace std;

class MikeUtilsTestTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeUtilsTestTest);
  CPPUNIT_TEST(testingEvalTest);
  CPPUNIT_TEST(testingEvalFileTest);
  CPPUNIT_TEST_SUITE_END();
private:
  Persistent<Context> cxt;
public:
  void setUp();
  void tearDown();
protected:
  void testingEvalTest();
  void testingEvalFileTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeUtilsTestTest);

void MikeUtilsTestTest::setUp()
{
  HandleScope scope;
  cxt = Context::New();
  cxt->Enter();
}

void MikeUtilsTestTest::tearDown()
{
  cxt->Exit();
  cxt.Dispose();
}

// Function mike::TestingEval() should evaluate given string within current
// context and return true when everyhing goes fine and result value is
// not false.
void MikeUtilsTestTest::testingEvalTest()
{
  CPPUNIT_ASSERT(mike::TestingEval("var foo = 1; foo;") == true);
  CPPUNIT_ASSERT(mike::TestingEval("false;") == false);
}

// Function mike::TestingEvalFile() should read content from given file and
// evaluate it within current context.
void MikeUtilsTestTest::testingEvalFileTest()
{
  CPPUNIT_ASSERT(mike::TestingEvalFile("./fixtures/dummy.js") == true);
}

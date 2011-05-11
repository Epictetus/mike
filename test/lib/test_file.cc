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
  CPPUNIT_TEST_SUITE_END();
private:
  context::Window *window;
public:
  void setUp();
  void tearDown();
protected:
  void existsFuncTest();
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
  ASSERT_EVAL("File.exists('/tmp/test-exists')", True());
  ASSERT_EVAL("File.exists('/tmp/test-not-exists')", False());
  ASSERT_EVAL("File.exists()", Null());
}

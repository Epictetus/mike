#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "mike/utils/fs.h"

using namespace std;

class MikeUtilsFsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeUtilsFsTest);
  CPPUNIT_TEST(cantReadFileTest);
  CPPUNIT_TEST(readFileTest);
  CPPUNIT_TEST_SUITE_END();
protected:
  void cantReadFileTest();
  void readFileTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeUtilsFsTest);

void MikeUtilsFsTest::cantReadFileTest()
{
  CPPUNIT_ASSERT(mike::ReadFile("foobar.txt") == NULL);
}

void MikeUtilsFsTest::readFileTest()
{
  char *content = mike::ReadFile("./fixtures/dummy.txt");
  CPPUNIT_ASSERT(content != NULL);
  CPPUNIT_ASSERT(strcmp(content, "foo\n") == 0);
}

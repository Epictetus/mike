#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "mike/utils/string.h"

using namespace std;

class MikeUtilsStringTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeUtilsStringTest);
  CPPUNIT_TEST(strltrimTest);
  CPPUNIT_TEST(strrtrimTest);
  CPPUNIT_TEST(strtrimTest);
  CPPUNIT_TEST_SUITE_END();
protected:
  void strltrimTest();
  void strrtrimTest();
  void strtrimTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeUtilsStringTest);

void MikeUtilsStringTest::strltrimTest()
{
  char *testee = "foobar   ";
  CPPUNIT_ASSERT(string(strrtrim(testee)) == "foobar");
}

void MikeUtilsStringTest::strrtrimTest()
{
  char *testee = "    foobar";
  CPPUNIT_ASSERT(string(strrtrim(testee)) == "foobar");
}

void MikeUtilsStringTest::strtrimTest()
{
  char *testee = "   foobar   ";
  CPPUNIT_ASSERT(string(strtrim(testee)) == "foobar");
}

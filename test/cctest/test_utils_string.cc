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
  CPPUNIT_ASSERT(string(strrtrim("foobar   ")) == "foobar")
}

void MikeUtilsStringTest::strrtrimTest()
{
  CPPUNIT_ASSERT(string(strrtrim("   foobar")) == "foobar")
}

void MikeUtilsStringTest::strtrimTest()
{
  CPPUNIT_ASSERT(string(strtrim("   foobar   ")) == "foobar")
}

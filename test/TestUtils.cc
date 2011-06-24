#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "utils/Helpers.h"

using namespace std;
using namespace mike;

class MikeUtilsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeUtilsTest);
  CPPUNIT_TEST(testStrstrip);
  CPPUNIT_TEST(testXpathSanitize);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testStrstrip()
  {
    ASSERT_EQUAL(string(strstrip("   foo")), "foo");
    ASSERT_EQUAL(string(strstrip("   foo   ")), "foo");
    ASSERT_EQUAL(string(strstrip("foo   ")), "foo");
    ASSERT_EQUAL(string(strstrip("  foo \r\n  \n")), "foo");
  }

  void testXpathSanitize()
  {
    ASSERT_EQUAL(xpathSanitize("foo&bar"), "foo&amp;bar");
    ASSERT_EQUAL(xpathSanitize("foo\"bar"), "foo&quot;bar");
    ASSERT_EQUAL(xpathSanitize("foo'bar"), "foo\\'bar");
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeUtilsTest);

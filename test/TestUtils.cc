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
  CPPUNIT_TEST(testStrjoin);
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

  void testStrjoin()
  {
    string parts[3] = { "one", "two", "three" };
    ASSERT_EQUAL(strjoin(parts, 3), "onetwothree");
    ASSERT_EQUAL(strjoin(parts, 1), "one");
    ASSERT_EQUAL(strjoin(parts, 3, "|"), "one|two|three");
    ASSERT_EQUAL(strjoin(parts, 1, "|"), "one");
    ASSERT_EQUAL(strjoin(parts, 2, "|"), "one|two");
  }

  void testXpathSanitize()
  {
    ASSERT_EQUAL(xpathSanitize("foo&bar"), "foo&amp;bar");
    ASSERT_EQUAL(xpathSanitize("foo\"bar"), "foo&quot;bar");
    ASSERT_EQUAL(xpathSanitize("foo'bar"), "foo\\'bar");
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeUtilsTest);

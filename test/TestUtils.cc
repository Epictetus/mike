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
  CPPUNIT_TEST(testStrsplit);
  CPPUNIT_TEST(testIsIncluded);
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

  void testStrsplit()
  {
    vector<string> parts1 = strsplit(" Hello my world!   ");
    ASSERT_EQUAL(parts1.size(), 3);
    ASSERT_EQUAL(parts1[0], "Hello");
    ASSERT_EQUAL(parts1[1], "my");
    ASSERT_EQUAL(parts1[2], "world!");
    vector<string> parts2 = strsplit("hello:delim", ':');
    ASSERT_EQUAL(parts2.size(), 2);
    ASSERT_EQUAL(parts2[0], "hello");
    ASSERT_EQUAL(parts2[1], "delim");
  }

  void testXpathSanitize()
  {
    ASSERT_EQUAL(xpathSanitize("foo&bar"), "foo&amp;bar");
    ASSERT_EQUAL(xpathSanitize("foo\"bar"), "foo&quot;bar");
    ASSERT_EQUAL(xpathSanitize("foo'bar"), "foo\\'bar");
  }

  void testIsIncluded()
  {
    string opts[3] = { "one", "two", "three" };
    ASSERT(isIncluded("one", opts, 3));
    ASSERT_NOT(isIncluded("foo", opts, 3));
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeUtilsTest);

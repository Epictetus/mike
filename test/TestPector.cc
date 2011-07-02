#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "utils/Helpers.h"
#include "utils/Pector.h"

using namespace std;
using namespace mike;

class MikePectorTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikePectorTest);
  CPPUNIT_TEST(testCreateEmpty);
  CPPUNIT_TEST(testCreateAndAssign);
  CPPUNIT_TEST(testClear);
  CPPUNIT_TEST(testPushBack);
  CPPUNIT_TEST(testPopBack);
  CPPUNIT_TEST(testFront);
  CPPUNIT_TEST(testBack);
  CPPUNIT_TEST(testBegin);
  CPPUNIT_TEST(testEnd);
  CPPUNIT_TEST(testPick);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testCreateEmpty()
  {
    Pector<int> pv = Pector<int>();
    ASSERT(pv.empty());
  }
  
  void testCreateAndAssign()
  {
    int* items[3] = {new int(1), new int(2), new int(3)};
    Pector<int> pv = Pector<int>(items, 3);
    ASSERT_EQUAL(pv.size(), 3);
  }

  void testClear()
  {
    int* items[3] = {new int(1), new int(2), new int(3)};
    Pector<int> pv = Pector<int>(items, 3);
    pv.clear();
    ASSERT(pv.empty());
  }

  void testPushBack()
  {
    Pector<int> pv = Pector<int>();
    pv.push_back(new int(10));
    ASSERT_EQUAL(pv.size(), 1);
    ASSERT_EQUAL(*pv[0], 10);
  }

  void testPopBack()
  {
    int* items[1] = {new int(1)};
    Pector<int> pv = Pector<int>(items, 1);
    ASSERT_NOT(pv.empty());
    pv.pop_back();
    ASSERT(pv.empty());
  }

  void testFront()
  {
    int* items[3] = {new int(1), new int(2), new int(3)};
    Pector<int> pv = Pector<int>(items, 3);
    ASSERT_EQUAL(*pv.front(), 1);
  }

  void testBack()
  {
    int* items[3] = {new int(1), new int(2), new int(3)};
    Pector<int> pv = Pector<int>(items, 3);
    ASSERT_EQUAL(*pv.back(), 3);
  }

  void testBegin()
  {
    int* items[3] = {new int(1), new int(2), new int(3)};
    Pector<int> pv = Pector<int>(items, 3);
    ASSERT_EQUAL(**pv.begin(), 1);
  }

  void testEnd()
  {
    int* items[3] = {new int(1), new int(2), new int(3)};
    Pector<int> pv = Pector<int>(items, 3);
    ASSERT_EQUAL(**(--pv.end()), 3);
  }

  void testPick()
  {
    int* items[3] = {new int(1), new int(2), new int(3)};
    Pector<int> pv = Pector<int>(items, 3);
    int* picked = pv.pick(1);
    ASSERT_EQUAL(pv.size(), 2);
    ASSERT_EQUAL(*pv[0], 1);
    ASSERT_EQUAL(*pv[1], 3);
    ASSERT_EQUAL(*picked, 2);
    delete picked;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikePectorTest);

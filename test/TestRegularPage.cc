#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "RegularPage.h"

using namespace std;
using namespace mike;

class MikeRegularPageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeRegularPageTest);
  CPPUNIT_TEST(testBuild);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuild()
  {
    Page* page = Page::Open("http://localhost:4567/simple.txt");
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple.txt");
    ASSERT(page->isRegular());
    ASSERT(page->toRegularPage());
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeRegularPageTest);

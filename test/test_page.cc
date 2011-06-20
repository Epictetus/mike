#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "mike/utils/test_macros.h"
#include "page.h"

using namespace std;
using namespace mike;

class MikePageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikePageTest);
  CPPUNIT_TEST(testBuildXml);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuildXml()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple.xml");
    Page* page = Page::Build(request);
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple.xml");
    ASSERT(page->isXml());
    ASSERT(page->toXmlPage());
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikePageTest);

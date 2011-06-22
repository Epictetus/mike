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
  CPPUNIT_TEST(testGetContent);
  CPPUNIT_TEST(testGetStream);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuild()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple.txt");
    Page* page = Page::Build(request);
    ASSERT(page && page->isLoaded());
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple.txt");
    ASSERT(page->isRegular());
    ASSERT(page->toRegularPage());
    delete page;
  }

  void testGetContent()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple.txt");
    RegularPage* page = Page::Build(request)->toRegularPage();
    ASSERT(page && page->isLoaded());
    ASSERT_EQUAL(page->getContent(), "Simple!");
    delete page;
  }
  
  void testGetStream()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple.txt");
    RegularPage* page = Page::Build(request)->toRegularPage();
    ASSERT(page && page->isLoaded());
    ASSERT_NOT_NULL(page->getStream());
    ASSERT_EQUAL(page->getStream()->str(), "Simple!");
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeRegularPageTest);

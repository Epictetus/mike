#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "Page.h"
#include "Browser.h"

using namespace std;
using namespace mike;

class MikePageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikePageTest);
  CPPUNIT_TEST(testBuildWhenInvalid);
  CPPUNIT_TEST(testGetContent);
  CPPUNIT_TEST(testGetStream);
  CPPUNIT_TEST(testGetEnclosingFrame);
  CPPUNIT_TEST(testGetEnclosingWindow);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuildWhenInvalid()
  {
    http::Request* request = http::Request::Get("http://thiswebsiteforsure/not/exists");
    Page* page = Page::Build(request);
    ASSERT_NOT(page->isLoaded());
    delete page;
  }

  void testGetContent()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple.txt");
    Page* page = Page::Build(request);
    ASSERT(page && page->isLoaded());
    ASSERT_EQUAL(page->getContent(), "Simple!");
    delete page;
  }
  
  void testGetStream()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple.txt");
    Page* page = Page::Build(request);
    ASSERT(page && page->isLoaded());
    ASSERT_NOT_NULL(page->getStream());
    ASSERT_EQUAL(page->getStream()->str(), "Simple!");
    delete page;
  }

  void testGetEnclosingFrame()
  {
    Browser* browser = new Browser();
    //browser->open()
    delete browser;
  }

  void testGetEnclosingWindow()
  {
    
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(MikePageTest);

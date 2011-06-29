#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "Page.h"
#include "Browser.h"

using namespace std;
using namespace mike;
using namespace mike::http;

class MikePageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikePageTest);
  CPPUNIT_TEST(testOpen);
  CPPUNIT_TEST(testBuildWhenInvalid);
  CPPUNIT_TEST(testGetContent);
  CPPUNIT_TEST(testGetStream);
  CPPUNIT_TEST(testGetEnclosingFrame);
  CPPUNIT_TEST(testGetEnclosingWindow);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testOpen()
  {
    Page* page = Page::Open("http://localhost:4567/simple");
    ASSERT_EQUAL(page->getContent(), "Kukuryku!");
    delete page;
  }
  
  void testBuildWhenInvalid()
  {
    Request* request = Request::Get("http://thiswebsiteforsure/not/exists");
    ASSERT_THROW(Page::Build(request), ConnectionError);
  }

  void testGetContent()
  {
    Page* page = Page::Open("http://localhost:4567/simple.txt");
    ASSERT_EQUAL(page->getContent(), "Simple!");
    delete page;
  }
  
  void testGetStream()
  {
    Page* page = Page::Open("http://localhost:4567/simple.txt");;
    ASSERT_NOT_NULL(page->getStream());
    ASSERT_EQUAL(page->getStream()->str(), "Simple!");
    delete page;
  }

  void testGetEnclosingFrame()
  {
    // TODO: ...
  }

  void testGetEnclosingWindow()
  {
    // TODO: ...
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(MikePageTest);

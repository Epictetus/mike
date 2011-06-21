#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "xml/XmlPage.h"

using namespace std;
using namespace mike;

class MikeXmlPageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeXmlPageTest);
  CPPUNIT_TEST(testBuild);
  CPPUNIT_TEST(testGetElementsByTagName);
  CPPUNIT_TEST(testGetElementsByXpath);
  CPPUNIT_TEST(testGetElementsByXpathOnInvalidDoc);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuild()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple.xml");
    Page* page = Page::Build(request);
    ASSERT(page && page->isLoaded());
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple.xml");
    ASSERT(page->isXml());
    ASSERT(page->toXmlPage());
    delete page;
  }

  void testGetElementsByTagName()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xpath.xml");
    XmlPage* page = Page::Build(request)->toXmlPage();
    ASSERT(page && page->isLoaded());
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    ASSERT_EQUAL(elems.size(), 3);
    elems.clear();
    delete page;
  }
  
  void testGetElementsByXpath()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xpath.xml");
    XmlPage* page = Page::Build(request)->toXmlPage();
    ASSERT(page->isLoaded());
    vector<XmlElement*> elems = page->getElementsByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elems.size(), 2);
    elems.clear();
    delete page;
  }

  void testGetElementsByXpathOnInvalidDoc()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple");
    XmlPage* page = Page::Build(request)->toXmlPage();
    ASSERT(page->isLoaded());
    vector<XmlElement*> elems = page->getElementsByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elems.size(), 0);
    elems.clear();
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeXmlPageTest);

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "mike/utils/test_macros.h"
#include "xml/xml_page.h"

using namespace std;
using namespace mike;

class MikeXmlPageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeXmlPageTest);
  CPPUNIT_TEST(testBuild);
  CPPUNIT_TEST(testGetElementsByTagName);
  CPPUNIT_TEST(testGetElementsByXpath);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuild()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple.xml");
    Page* page = Page::Build(request);
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple.xml");
    ASSERT(page->isXml());
    ASSERT(page->toXmlPage());
    delete page;
  }

  void testGetElementsByTagName()
  {
    
  }
  
  void testGetElementsByXpath()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xpath.xml");
    XmlPage* page = Page::Build(request)->toXmlPage();
    vector<XmlElement*> elems = page->getElementsByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elems.size(), 2);
    elems.clear();
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeXmlPageTest);

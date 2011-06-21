#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "xml/XmlPage.h"

using namespace std;
using namespace mike;

class MikeXmlElementTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeXmlElementTest);
  CPPUNIT_TEST(testGetAttribute);
  CPPUNIT_TEST(testHasAttribute);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testGetAttribute()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xml-elements.xml");
    XmlPage* page = Page::Build(request)->toXmlPage();
    ASSERT(page);
    XmlElement* elem = page->getElementsByTagName("elem")[0];
    ASSERT_NOT_NULL(elem);
    ASSERT_EQUAL(elem->getAttribute("foo"), "bar");
    ASSERT_EQUAL(elem->getAttribute("foo"), "bar"); // it has to be done twice here, to test attrs cache...
    ASSERT_EQUAL(elem->getAttribute("bar"), "");
    delete elem;
    delete page;
  }

  void testHasAttribute()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xml-elements.xml");
    XmlPage* page = Page::Build(request)->toXmlPage();
    ASSERT(page);
    XmlElement* elem = page->getElementsByTagName("elem")[0];
    ASSERT_NOT_NULL(elem);
    ASSERT(elem->hasAttribute("foo"));
    ASSERT_NOT(elem->hasAttribute("bar"));
    delete elem;
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeXmlElementTest);

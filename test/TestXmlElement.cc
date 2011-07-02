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
  CPPUNIT_TEST(testGetContent);
  CPPUNIT_TEST(testHasContent);
  CPPUNIT_TEST(testGetName);
  CPPUNIT_TEST(testGetPath);
  CPPUNIT_TEST(testDump);
  CPPUNIT_TEST(testHasChildren);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testGetAttribute()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    XmlElementSet* elems = page->getElementsByTagName("elem");
    XmlElement* elem = (*elems)[0];
    ASSERT_EQUAL(elem->getAttribute("foo"), "bar");
    ASSERT_EQUAL(elem->getAttribute("foo"), "bar"); // it has to be done twice here, to test attrs cache...
    ASSERT_EQUAL(elem->getAttribute("bar"), "");
    delete elems;
    delete page;
  }

  void testHasAttribute()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    XmlElementSet* elems = page->getElementsByTagName("elem");
    XmlElement* elem = (*elems)[0];
    ASSERT(elem->hasAttribute("foo"));
    ASSERT_NOT(elem->hasAttribute("bar"));
    ASSERT(elem->hasAttribute("foo", "bar"));
    ASSERT_NOT(elem->hasAttribute("foo", "not-like-this"));
    delete elems;
    delete page;
  }

  void testGetContent()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    XmlElementSet* elems = page->getElementsByTagName("elem");
    ASSERT_EQUAL(elems->size(), 2);
    ASSERT_EQUAL(elems->get(0)->getContent(), "Hello Foo!");
    ASSERT_EQUAL(elems->get(1)->getContent(), "Hello sub!");
    delete elems;
    delete page;
  }

  void testHasContent()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    XmlElementSet* elems = page->getElementsByTagName("elem");
    XmlElement* elem = (*elems)[0];
    ASSERT(elem->hasContent("Hello Foo!"));
    ASSERT_NOT(elem->hasContent("Not like this!"));
    ASSERT(elem->hasContent());
    delete elems;
    delete page;
  }

  void testGetName()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    XmlElementSet* elems = page->getElementsByTagName("elem");
    XmlElement* elem = (*elems)[0];
    ASSERT_EQUAL(elem->getName(), "elem");
    delete elems;
    delete page;
  }

  void testGetPath()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    XmlElementSet* elems = page->getElementsByTagName("elem");
    ASSERT_EQUAL(elems->get(0)->getPath(), "/root/elem[1]");
    ASSERT_EQUAL(elems->get(1)->getPath(), "/root/elem[2]");
    delete elems;
    delete page;
  }

  void testDump()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    XmlElementSet* elems = page->getElementsByTagName("elem");
    XmlElement* elem = (*elems)[1];
    ASSERT_EQUAL(elem->toXml(), "<elem><sub>Hello</sub> sub!</elem>");
    ASSERT_EQUAL(elem->dump(), "<elem><sub>Hello</sub> sub!</elem>");
    delete elems;
    delete page;
  }
  
  void testHasChildren()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/anchors.html");
    XmlElementSet* elems1 = page->getElementsByTagName("a");
    XmlElement* elem1 = (*elems1)[0];
    ASSERT(elem1->hasChildren());
    XmlElementSet* elems2 = page->getElementsByTagName("input");
    XmlElement* elem2 = (*elems2)[0];
    ASSERT_NOT(elem2->hasChildren());
    delete elems1;
    delete elems2;
    delete page;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeXmlElementTest);

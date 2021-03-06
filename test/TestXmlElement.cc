#include "test/Macros.h"

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
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    XmlElement* elem = elems[0];
    ASSERT_EQUAL(elem->getAttribute("foo"), "bar");
    ASSERT_EQUAL(elem->getAttribute("bar"), "");
    delete page;
  }

  void testHasAttribute()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    XmlElement* elem = elems[0];
    ASSERT(elem->hasAttribute("foo"));
    ASSERT_NOT(elem->hasAttribute("bar"));
    ASSERT(elem->hasAttribute("foo", "bar"));
    ASSERT_NOT(elem->hasAttribute("foo", "not-like-this"));
    delete page;
  }

  void testGetContent()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    ASSERT_EQUAL(elems.size(), 2);
    ASSERT_EQUAL(elems[0]->getContent(), "Hello Foo!");
    ASSERT_EQUAL(elems[1]->getContent(), "Hello sub!");
    delete page;
  }

  void testHasContent()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    XmlElement* elem = elems[0];
    ASSERT(elem->hasContent("Hello Foo!"));
    ASSERT_NOT(elem->hasContent("Not like this!"));
    ASSERT(elem->hasContent());
    delete page;
  }

  void testGetName()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    XmlElement* elem = elems[0];
    ASSERT_EQUAL(elem->getTagName(), "elem");
    delete page;
  }

  void testGetPath()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    ASSERT_EQUAL(elems[0]->getPath(), "/root/elem[1]");
    ASSERT_EQUAL(elems[1]->getPath(), "/root/elem[2]");
    delete page;
  }

  void testDump()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xml-elements.xml");
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    XmlElement* elem = elems[1];
    ASSERT_EQUAL(elem->toXml(), "<elem><sub>Hello</sub> sub!</elem>");
    ASSERT_EQUAL(elem->dump(), "<elem><sub>Hello</sub> sub!</elem>");
    delete page;
  }
  
  void testHasChildren()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/anchors.html");
    vector<XmlElement*> elems = page->getElementsByTagName("a");
    ASSERT(elems[0]->hasChildren());
    elems = page->getElementsByTagName("input");
    ASSERT_NOT(elems[0]->hasChildren());
    delete page;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeXmlElementTest);

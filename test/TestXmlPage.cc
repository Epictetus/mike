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
  CPPUNIT_TEST(testFactory);
  CPPUNIT_TEST(testGetElementsByTagName);
  CPPUNIT_TEST(testGetElementsByXpath);
  CPPUNIT_TEST(testGetElementByXpath);
  CPPUNIT_TEST(testGetElementByXpathWhenElementNotFound);
  CPPUNIT_TEST(testGetElementsByXpathWhenInvalidExpression);
  CPPUNIT_TEST(testGetElementsByXpathOnInvalidDoc);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testFactory()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple.xml");
    ASSERT(page->isXml());
    delete page;
  }

  void testGetElementsByTagName()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xpath.xml");
    XmlElementSet* elems = page->getElementsByTagName("elem");
    ASSERT_EQUAL(elems->size(), 3);
    delete elems;
    delete page;
  }
  
  void testGetElementsByXpath()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xpath.xml");
    XmlElementSet* elems = page->getElementsByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elems->size(), 2);
    delete elems;
    delete page;
  }

  void testGetElementByXpath()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xpath.xml");
    XmlElement* elem = page->getElementByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elem->getContent(), "First");
    delete elem;
    delete page;
  }

  void testGetElementByXpathWhenElementNotFound()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xpath.xml");
    ASSERT_THROW(page->getElementByXpath("//root/forsurenotfound"), ElementNotFoundError);
    delete page;
  }

  void testGetElementsByXpathWhenInvalidExpression()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xpath.xml");
    ASSERT_THROW(page->getElementsByXpath("//root//elems%$///this/.../is/broken"), InvalidXpathExpressionError);
    delete page;
  }
  
  void testGetElementsByXpathOnInvalidDoc()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/simple");
    XmlElementSet* elems = page->getElementsByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elems->size(), 0);
    delete elems;
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeXmlPageTest);

#include "test/Macros.h"

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
  CPPUNIT_TEST(testGetElementByPath);
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
    vector<XmlElement*> elems = page->getElementsByTagName("elem");
    ASSERT_EQUAL(elems.size(), 3);
    delete page;
  }
  
  void testGetElementsByXpath()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xpath.xml");
    vector<XmlElement*> elems = page->getElementsByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elems.size(), 2);
    delete page;
  }

  void testGetElementByPath()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xpath.xml");
    XmlElement* elem = page->getElementByPath("/root/elems/elem[2]");
    ASSERT_EQUAL(elem->getContent(), "Second");
    elem = page->getElementByPath("/root/elems/elem");
    ASSERT_EQUAL(elem->getContent(), "First");
    ASSERT_THROW(page->getElementByPath("/root/elems/elem[0]"), ElementNotFoundError);
    delete page;
  }

  void testGetElementByXpath()
  {
    XmlPage* page = (XmlPage*)Page::Open("http://localhost:4567/xpath.xml");
    XmlElement* elem = page->getElementByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elem->getContent(), "First");
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
    vector<XmlElement*> elems = page->getElementsByXpath("//root//elems/elem[@load]");
    ASSERT_EQUAL(elems.size(), 0);
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeXmlPageTest);

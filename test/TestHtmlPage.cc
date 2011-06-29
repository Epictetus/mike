#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "html/HtmlPage.h"

using namespace std;
using namespace mike;

class MikeHtmlPageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeHtmlPageTest);
  CPPUNIT_TEST(testBuild);
  CPPUNIT_TEST(testGetElementsByTagName);
  CPPUNIT_TEST(testGetElementsByXpath);
  CPPUNIT_TEST(testGetElementById);
  CPPUNIT_TEST(testGetElementsByClassName);
  CPPUNIT_TEST(testGetElementByAnchor);
  CPPUNIT_TEST(testGetFramesWithIframes);
  CPPUNIT_TEST(testGetFramesWithFrameset);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuild()
  {
    Page* page = Page::Open("http://localhost:4567/simple");
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple");
    ASSERT(page->isHtml());
    ASSERT(page->toHtmlPage());
    delete page;
  }

  void testGetElementsByTagName()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    XmlElementSet* elems = page->getElementsByTagName("li");
    ASSERT_EQUAL(elems->size(), 3);
    delete elems;
    delete page;
  }
  
  void testGetElementsByXpath()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    XmlElementSet* elems = page->getElementsByXpath("//ul[@id='elems']/li[contains(@class, 'load')]");
    ASSERT_EQUAL(elems->size(), 2);
    delete elems;
    delete page;
  }

  void testGetElementById()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    XmlElement* should_be_found = page->getElementById("elems");
    XmlElement* should_not_be_found = page->getElementById("not-found");
    ASSERT_NOT_NULL(should_be_found);
    ASSERT_NULL(should_not_be_found);
    delete should_be_found;
    delete should_not_be_found;
    delete page;
  }

  void testGetElementsByClassName()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    XmlElementSet* elems_ok = page->getElementsByClassName("load");
    XmlElementSet* elems_not_ok = page->getElementsByClassName("loa");
    XmlElementSet* elems_not_ok_too = page->getElementsByClassName("load fo");
    ASSERT_EQUAL(elems_ok->size(), 2);
    ASSERT_EQUAL(elems_not_ok->size(), 0);
    ASSERT_EQUAL(elems_not_ok_too->size(), 0);
    delete elems_ok;
    delete elems_not_ok;
    delete elems_not_ok_too;
    delete page;
  }

  void testGetElementByAnchor()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    XmlElement* should_be_found1 = page->getElementByAnchor("I am a link!");
    XmlElement* should_be_found2 = page->getElementByAnchor("I am a button!");
    XmlElement* should_be_found3 = page->getElementByAnchor("I am a submit!");
    XmlElement* should_not_be_found = page->getElementByAnchor("I am a div!");
    ASSERT_NOT_NULL(should_be_found1);
    ASSERT_EQUAL(should_be_found1->getName(), "a");
    ASSERT_NOT_NULL(should_be_found2);
    ASSERT_EQUAL(should_be_found2->getName(), "button");
    ASSERT_NOT_NULL(should_be_found3);
    ASSERT_EQUAL(should_be_found3->getName(), "input");
    ASSERT_NULL(should_not_be_found);
    delete should_be_found1;
    delete should_be_found2;
    delete should_be_found3;
    delete should_not_be_found;
    delete page;
  }

  void testGetFramesWithIframes()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/iframes.html");
    XmlElementSet* frames = page->getFrames();
    ASSERT_EQUAL(frames->size(), 2);
    delete frames;
    delete page;
  }
  
  void testGetFramesWithFrameset()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/frameset.html");
    XmlElementSet* frames = page->getFrames();
    ASSERT_EQUAL(frames->size(), 2);
    delete frames;
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHtmlPageTest);

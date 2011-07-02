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
  CPPUNIT_TEST(testFactory);
  CPPUNIT_TEST(testGetElementsByTagName);
  CPPUNIT_TEST(testGetElementsByXpath);
  CPPUNIT_TEST(testGetElementById);
  CPPUNIT_TEST(testGetElementsByClassName);
  CPPUNIT_TEST(testGetLinkOrButtonAgainstLink);
  CPPUNIT_TEST(testGetLinkOrButtonAgainstButton);
  CPPUNIT_TEST(testGetLinkOrButtonAgainstSubmit);
  CPPUNIT_TEST(testGetLinkOrButtonAgainstDiv);
  CPPUNIT_TEST(testGetLink);
  CPPUNIT_TEST(testGetButton);
  CPPUNIT_TEST(testGetField);
  //CPPUNIT_TEST(testGetFramesWithIframes);
  //CPPUNIT_TEST(testGetFramesWithFrameset);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testFactory()
  {
    Page* page = Page::Open("http://localhost:4567/simple");
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple");
    ASSERT(page->isHtml());
    delete page;
  }

  void testGetElementsByTagName()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    HtmlElementSet* elems = page->getElementsByTagName("li");
    ASSERT_EQUAL(elems->size(), 3);
    delete elems;
    delete page;
  }
  
  void testGetElementsByXpath()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    HtmlElementSet* elems = page->getElementsByXpath("//ul[@id='elems']/li[contains(@class, 'load')]");
    ASSERT_EQUAL(elems->size(), 2);
    delete elems;
    delete page;
  }

  void testGetElementById()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    HtmlElement* should_be_found = page->getElementById("elems");
    ASSERT_NOT_NULL(should_be_found);
    ASSERT_THROW(page->getElementById("not-found"), ElementNotFoundError);
    delete should_be_found;
    delete page;
  }

  void testGetElementsByClassName()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    HtmlElementSet* elems_ok = page->getElementsByClassName("load");
    HtmlElementSet* elems_not_ok = page->getElementsByClassName("loa");
    HtmlElementSet* elems_not_ok_too = page->getElementsByClassName("load fo");
    ASSERT_EQUAL(elems_ok->size(), 2);
    ASSERT_EQUAL(elems_not_ok->size(), 0);
    ASSERT_EQUAL(elems_not_ok_too->size(), 0);
    delete elems_ok;
    delete elems_not_ok;
    delete elems_not_ok_too;
    delete page;
  }

  // TODO: test finding links/buttons by name and id!
  
  void testGetLinkOrButtonAgainstLink()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* link = page->getLinkOrButton("I am a link!");
    ASSERT_EQUAL(link->getName(), "a");
    ASSERT(link->hasAttribute("name", "link"));
    link = page->getLinkOrButton("link");
    ASSERT_EQUAL(link->getName(), "a");
    delete link;
    delete page;
  }

  void testGetLinkOrButtonAgainstButton()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* button = page->getLinkOrButton("I am a button!");
    ASSERT_EQUAL(button->getName(), "button");
    ASSERT(button->hasAttribute("id", "buuu"));
    button = page->getLinkOrButton("buuu");
    ASSERT_EQUAL(button->getName(), "button");
    delete button;
    delete page;
  }

  void testGetLinkOrButtonAgainstSubmit()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* submit = page->getLinkOrButton("I am a submit!");
    ASSERT_EQUAL(submit->getName(), "input");
    ASSERT(submit->hasAttribute("name", "foo"));
    submit = page->getLinkOrButton("foo");
    ASSERT_EQUAL(submit->getName(), "input");
    delete submit;
    delete page;
  }

  void testGetLinkOrButtonAgainstDiv()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    ASSERT_THROW(page->getLinkOrButton("I am a div!"), ElementNotFoundError);
    delete page;
  }

  void testGetLink()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* link = page->getLinkOrButton("I am a link!");
    ASSERT_EQUAL(link->getName(), "a");
    delete link;
    delete page;
  }

  void testGetButton()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* button = page->getLinkOrButton("I am a button!");
    ASSERT_EQUAL(button->getName(), "button");
    HtmlElement* submit = page->getLinkOrButton("I am a submit!");
    ASSERT_EQUAL(submit->getName(), "input");
    delete button;
    delete submit;
    delete page;
  }

  void testGetField()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/fields.html");
    HtmlElement* input = page->getField("foo");
    ASSERT(input->hasAttribute("name", "foo"));
    HtmlElement* password = page->getField("pass");
    ASSERT(password->hasAttribute("id", "pass"));
    HtmlElement* select = page->getField("opts");
    ASSERT(select->hasAttribute("id", "opts"));
    ASSERT_EQUAL(select->getName(), "select");
    HtmlElement* textarea = page->getField("Hello label!");
    ASSERT(textarea->hasAttribute("id", "bar"));
    delete textarea;
    delete select;
    delete password;
    delete input;
    delete page;
  }
  
  /*
  void testGetFramesWithIframes()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/iframes.html");
    HtmlElementSet* frames = page->getFrames();
    ASSERT_EQUAL(frames->size(), 2);
    delete frames;
    delete page;
  }
  
  void testGetFramesWithFrameset()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/frameset.html");
    HtmlElementSet* frames = page->getFrames();
    ASSERT_EQUAL(frames->size(), 2);
    delete frames;
    delete page;
  }
  */
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHtmlPageTest);

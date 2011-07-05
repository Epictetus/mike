#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "html/HtmlPage.h"
#include "Browser.h"

using namespace std;
using namespace mike;

class MikeHtmlPageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeHtmlPageTest);
  CPPUNIT_TEST(testFactory);
  CPPUNIT_TEST(testGetElementsByTagName);
  CPPUNIT_TEST(testGetElementsByXpath);
  CPPUNIT_TEST(testGetElementById);
  CPPUNIT_TEST(testGetElementWhenNoLocatorTypeSpecified);
  CPPUNIT_TEST(testGetElementWhenLocatorTypeSpecified);
  CPPUNIT_TEST(testGetElementsByClassName);
  CPPUNIT_TEST(testGetLinkOrButtonAgainstLink);
  CPPUNIT_TEST(testGetLinkOrButtonAgainstButton);
  CPPUNIT_TEST(testGetLinkOrButtonAgainstSubmit);
  CPPUNIT_TEST(testGetLinkOrButtonAgainstDiv);
  CPPUNIT_TEST(testGetLink);
  CPPUNIT_TEST(testGetButton);
  CPPUNIT_TEST(testGetField);
  CPPUNIT_TEST(testGetTitle);
  CPPUNIT_TEST(testGetFramesWithIframes);
  CPPUNIT_TEST(testGetFramesWithFrameset);
  CPPUNIT_TEST(testDiscardNoScriptElementsWhenJavaScriptEnabled);
  CPPUNIT_TEST(testNoScriptElementsWhenJavaScriptDisabled);
  CPPUNIT_TEST(testSimpleJavaScript);
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
    vector<HtmlElement*> elems = page->getElementsByTagName("li");
    ASSERT_EQUAL(elems.size(), 3);
    delete page;
  }
  
  void testGetElementsByXpath()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    vector<HtmlElement*> elems = page->getElementsByXpath("//ul[@id='elems']/li[contains(@class, 'load')]");
    ASSERT_EQUAL(elems.size(), 2);
    delete page;
  }

  void testGetElementById()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    HtmlElement* should_be_found = page->getElementById("elems");
    ASSERT_NOT_NULL(should_be_found);
    ASSERT_THROW(page->getElementById("not-found"), ElementNotFoundError);
    delete page;
  }

  void testGetElementWhenLocatorTypeSpecified()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* elem;
    elem = page->getElement(BY_XPATH, "//a");
    ASSERT_EQUAL(elem->getText(), "I am a link!");
    elem = page->getElement(BY_ID, "buuu");
    ASSERT_EQUAL(elem->getText(), "I am a button!");
    elem = page->getElement(BY_PATH, "/html/body/a[1]");
    ASSERT_EQUAL(elem->getText(), "I am a link!");
    //elem = page->getElement(BY_CSS, "#buuu");
    //ASSERT_EQUAL(elem->getText(), "I am a button!");
    //delete elem;
    delete page;
  }
  
  void testGetElementWhenNoLocatorTypeSpecified()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* elem = page->getElement("I am a link!");
    ASSERT_EQUAL(elem->getTagName(), "a");
    delete page;
  }
  
  void testGetElementsByClassName()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/xpath.html");
    vector<HtmlElement*> elems_ok = page->getElementsByClassName("load");
    vector<HtmlElement*> elems_not_ok = page->getElementsByClassName("loa");
    vector<HtmlElement*> elems_not_ok_too = page->getElementsByClassName("load fo");
    ASSERT_EQUAL(elems_ok.size(), 2);
    ASSERT_EQUAL(elems_not_ok.size(), 0);
    ASSERT_EQUAL(elems_not_ok_too.size(), 0);
    delete page;
  }

  // TODO: test finding links/buttons by name and id!
  
  void testGetLinkOrButtonAgainstLink()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* link = page->getLinkOrButton("I am a link!");
    ASSERT_EQUAL(link->getTagName(), "a");
    ASSERT(link->hasAttribute("name", "link"));
    link = page->getLinkOrButton("link");
    ASSERT_EQUAL(link->getTagName(), "a");
    delete page;
  }

  void testGetLinkOrButtonAgainstButton()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* button = page->getLinkOrButton("I am a button!");
    ASSERT_EQUAL(button->getTagName(), "button");
    ASSERT(button->hasAttribute("id", "buuu"));
    button = page->getLinkOrButton("buuu");
    ASSERT_EQUAL(button->getTagName(), "button");
    delete page;
  }

  void testGetLinkOrButtonAgainstSubmit()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* submit = page->getLinkOrButton("I am a submit!");
    ASSERT_EQUAL(submit->getTagName(), "input");
    ASSERT(submit->hasAttribute("name", "foo"));
    submit = page->getLinkOrButton("foo");
    ASSERT_EQUAL(submit->getTagName(), "input");
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
    ASSERT_EQUAL(link->getTagName(), "a");
    delete page;
  }

  void testGetButton()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    HtmlElement* button = page->getLinkOrButton("I am a button!");
    ASSERT_EQUAL(button->getTagName(), "button");
    HtmlElement* submit = page->getLinkOrButton("I am a submit!");
    ASSERT_EQUAL(submit->getTagName(), "input");
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
    ASSERT_EQUAL(select->getTagName(), "select");
    HtmlElement* textarea = page->getField("Hello label!");
    ASSERT(textarea->hasAttribute("id", "bar"));
    delete page;
  }

  void testGetTitle()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/with-title.html");
    ASSERT_EQUAL(page->getTitle(), "Hello World!");
    delete page;
    page = (HtmlPage*)Page::Open("http://localhost:4567/simple.html");
    ASSERT_EQUAL(page->getTitle(), "");
    delete page;
  }
  
  void testGetFramesWithIframes()
  {
    Browser* browser = new Browser();
    HtmlPage* page = (HtmlPage*)browser->open("http://localhost:4567/iframes.html");
    vector<HtmlFrame*> frames = page->getFrames();
    ASSERT_EQUAL(frames.size(), 2);
    ASSERT_EQUAL(frames[0]->getPage()->getUrl(), "http://localhost:4567/iframes/1.html");
    delete browser;
  }
  
  void testGetFramesWithFrameset()
  {
    Browser* browser = new Browser();
    HtmlPage* page = (HtmlPage*)browser->open("http://localhost:4567/frameset.html");
    vector<HtmlFrame*> frames = page->getFrames();
    ASSERT_EQUAL(frames.size(), 2);
    ASSERT_EQUAL(frames[0]->getPage()->getUrl(), "http://localhost:4567/iframes/1.html");
    delete browser;
  }

  void testDiscardNoScriptElementsWhenJavaScriptEnabled()
  {
    Browser* browser = new Browser();
    browser->enableJava();
    HtmlPage* page = (HtmlPage*)browser->open("http://localhost:4567/noscript.html");
    vector<HtmlElement*> noscripts = page->getElementsByXpath("//noscript//*");
    ASSERT(noscripts.empty());
    delete browser;
  }

  void testNoScriptElementsWhenJavaScriptDisabled()
  {
    Browser* browser = new Browser();
    browser->disableJava();
    HtmlPage* page = (HtmlPage*)browser->open("http://localhost:4567/noscript.html");
    vector<HtmlElement*> noscripts = page->getElementsByXpath("//noscript//*");
    ASSERT_NOT(noscripts.empty());
    delete browser;
  }

  void testSimpleJavaScript()
  {
    Browser* browser = new Browser();
    browser->enableJava();
    HtmlPage* page = (HtmlPage*)browser->open("http://localhost:4567/simple-js.html");
    page->evaluate("test+=1;");
    ASSERT_EQUAL(page->evaluate("test;"), "3");
    delete browser;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHtmlPageTest);

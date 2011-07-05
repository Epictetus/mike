#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "html/HtmlPage.h"

using namespace std;
using namespace mike;

class MikeHtmlElementTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeHtmlElementTest);
  CPPUNIT_TEST(testIsButton);
  CPPUNIT_TEST(testIsLink);
  CPPUNIT_TEST(testIsSelect);
  CPPUNIT_TEST(testIsField);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testIsButton()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    ASSERT(page->getElementByXpath("//button")->isButton());
    ASSERT(page->getElementByXpath("//input[@type='submit']")->isButton());
    delete page;
  }

  void testIsLink()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/anchors.html");
    ASSERT(page->getElementByXpath("//a")->isLink());
    delete page;
  }

  void testIsSelect()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/fields.html");
    ASSERT(page->getElementByXpath("//select")->isSelect());
    delete page;
  }

  void testIsField()
  {
    HtmlPage* page = (HtmlPage*)Page::Open("http://localhost:4567/fields.html");
    ASSERT(page->getElementByXpath("//input[@type='text']")->isField());
    ASSERT(page->getElementByXpath("//input[@type='password']")->isField());
    ASSERT_NOT(page->getElementByXpath("//select")->isField());
    ASSERT_NOT(page->getElementByXpath("//input[@type='submit']")->isField());
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHtmlElementTest);

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "html/HtmlPage.h"
#include "Window.h"
#include "Browser.h"

using namespace std;
using namespace mike;

class MikeJavaScriptWindowTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeJavaScriptWindowTest);
  CPPUNIT_TEST(testWindowAndThisObject);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testWindowAndThisObject()
  {
    Browser* browser = new Browser();
    PageRef<HtmlPage> page = (HtmlPage*)browser->open("http://localhost:4567/simple.html");
    ASSERT_EQUAL(page->evaluate("window == this ? 'y' : 'n'"), "y");
    ASSERT_EQUAL(page->evaluate("window = 'cantoverwrite'; window == this ? 'y' : 'n'"), "y");
    ASSERT_EQUAL(page->evaluate("window == window.window ? 'y' : 'n'"), "y");
    delete browser;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeJavaScriptWindowTest);

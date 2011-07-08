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
  CPPUNIT_TEST(testAnyExpectedAlert);
  CPPUNIT_TEST(testSpecificExpectedAlert);
  CPPUNIT_TEST(testUnexpectedAlerts);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testWindowAndThisObject()
  {
    Browser browser;
    PageRef<HtmlPage> page = (HtmlPage*)browser.open("http://localhost:4567/simple.html");
    ASSERT_EQUAL(page->evaluate("window == this"), "true");
    ASSERT_EQUAL(page->evaluate("window = 'cantoverwrite'; window == this;"), "true");
    ASSERT_EQUAL(page->evaluate("window == window.window"), "true");
    ASSERT_EQUAL(page->evaluate("window.constructor.toString()"), "function DOMWindow() { [native code] }");
  }

  void testAnyExpectedAlert()
  {
    Browser browser;
    browser.expectAlert();
    PageRef<HtmlPage> page = (HtmlPage*)browser.open("http://localhost:4567/alert.html");
  }

  void testSpecificExpectedAlert()
  {
    Browser browser;
    browser.expectAlert("Hello Alert!");
    PageRef<HtmlPage> page = (HtmlPage*)browser.open("http://localhost:4567/alert.html");
  }

  void testUnexpectedAlerts()
  {
    Browser browser;
    ASSERT_THROW(browser.open("http://localhost:4567/alert.html"), UnexpectedAlertError);
    browser.expectAlert("Hello Other Alert!");
    ASSERT_THROW(browser.open("http://localhost:4567/alert.html"), UnexpectedAlertError);
  }

  void testNotFullyMetExpectationsForAlerts()
  {
    // TODO: pending...
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeJavaScriptWindowTest);

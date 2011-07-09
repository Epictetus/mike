#include "test/Macros.h"

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
  CPPUNIT_TEST(testAnyExpectedConfirm);
  CPPUNIT_TEST(testSpecificExpectedConfirm);
  CPPUNIT_TEST(testUnexpectedConfirm);
  CPPUNIT_TEST(testNotFullyMetExpectations);
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

  void testAnyExpectedConfirm()
  {
    Browser browser;
    browser.expectConfirm(true);
    PageRef<HtmlPage> page = (HtmlPage*)browser.open("http://localhost:4567/confirm.html");
    ASSERT_EQUAL(page->evaluate("res"), "true");
  }

  void testSpecificExpectedConfirm()
  {
    Browser browser;
    browser.expectConfirm("Are you sure?", false);
    PageRef<HtmlPage> page = (HtmlPage*)browser.open("http://localhost:4567/confirm.html");
    ASSERT_EQUAL(page->evaluate("res"), "false");
  }

  void testUnexpectedConfirm()
  {
    Browser browser;
    ASSERT_THROW(browser.open("http://localhost:4567/confirm.html"), UnexpectedConfirmError);
    browser.expectConfirm("Foobar!", true);
    ASSERT_THROW(browser.open("http://localhost:4567/confirm.html"), UnexpectedConfirmError);
    browser.expectAlert("Bla!");
    ASSERT_THROW(browser.open("http://localhost:4567/confirm.html"), UnexpectedConfirmError);
  }

  void testNotFullyMetExpectations()
  {
    Browser browser;
    browser.expectConfirm("Foobar!");
    browser.expectAlert("Foobar!");
    ASSERT_THROW(browser.open("http://localhost:4567/confirm.html"), ExpectationNotMet);
  }  
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeJavaScriptWindowTest);

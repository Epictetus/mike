#include "test/Macros.h"

#include "Browser.h"
#include "Window.h"
#include "Page.h"
#include "Config.h"

using namespace std;
using namespace mike;

class MikeBrowserTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeBrowserTest);
  CPPUNIT_TEST(testLanguage);
  CPPUNIT_TEST(testDefaultUserAgent);
  CPPUNIT_TEST(testCustomUserAgent);
  CPPUNIT_TEST(testIsJavaEnabled);
  CPPUNIT_TEST(testIsCookieEnabled);
  CPPUNIT_TEST(testOpen);
  CPPUNIT_TEST(testGetWindows);
  CPPUNIT_TEST(testGetWindow);
  CPPUNIT_TEST(testCloseAll);
  CPPUNIT_TEST(testCloseWindowByPosition);
  CPPUNIT_TEST(testCloseWindowByObject);
  CPPUNIT_TEST(testEnabledCookiesHandling);
  CPPUNIT_TEST(testDisabledCookiesHandling);
  CPPUNIT_TEST(testWorkOnLineAndOffLine);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testLanguage()
  {
    Browser browser;
    ASSERT_EQUAL(browser.getLanguage(), "en");
    browser = Browser("pl");
    ASSERT_EQUAL(browser.getLanguage(), "pl");
  }

  void testDefaultUserAgent()
  {
    Browser browser;
    ASSERT_EQUAL(browser.getUserAgent(), "Mozilla/5.0 (Memory; " + string(OS_TYPE) + " " + string(CPU_ARCH)+") Mike/" + string(MIKE_VERSION) + " (Mike, like Gecko) Mike/1");
  }

  void testCustomUserAgent()
  {
    Browser browser("en", "my user agent string");
    ASSERT_EQUAL(browser.getUserAgent(), "my user agent string");
  }

  void testIsJavaEnabled()
  {
    Browser browser;
    ASSERT_EQUAL(browser.isJavaEnabled(), true);
    ASSERT_EQUAL(browser.isJavaScriptEnabled(), true);
    browser = Browser("en", "", true, false);
    ASSERT_EQUAL(browser.isJavaEnabled(), false);
  }

  void testIsCookieEnabled()
  {
    Browser browser;
    ASSERT_EQUAL(browser.isCookieEnabled(), true);
    browser = Browser("en", "", false);
    ASSERT_EQUAL(browser.isCookieEnabled(), false);
  }

  void testOpen()
  {
    Browser browser;
    Page* page = browser.open("http://localhost:4567/simple");
    ASSERT_NOT_NULL(page);
    ASSERT_EQUAL(page->getContent(), "Kukuryku!");
  }

  void testGetWindows()
  {
    Browser browser;
    browser.open("http://localhost:4567/simple.html");
    browser.open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser.getWindows().size(), 2);
  }

  void testGetWindow()
  {
    Browser browser;
    browser.open("http://localhost:4567/simple.html");
    browser.open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser.getWindow(1)->getUrl(), "http://localhost:4567/simple.xml");
    ASSERT_THROW(browser.getWindow(2), WindowNotExistsError);
  }

  void testCloseAll()
  {
    Browser browser;
    browser.open("http://localhost:4567/simple.html");
    browser.open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser.getWindows().size(), 2);
    browser.closeAll();
    ASSERT_EQUAL(browser.getWindows().size(), 0);
  }

  void testCloseWindowByPosition()
  {
    Browser browser;
    browser.open("http://localhost:4567/simple.html");
    browser.open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser.getWindows().size(), 2);
    browser.closeWindow(0);
    ASSERT_EQUAL(browser.getWindows().size(), 1);
    ASSERT_EQUAL(browser.getWindow(0)->getUrl(), "http://localhost:4567/simple.xml");
  }

  void testCloseWindowByObject()
  {
    Browser browser;
    browser.open("http://localhost:4567/simple.html");
    browser.open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser.getWindows().size(), 2);
    browser.closeWindow(browser.getWindow(0));
    ASSERT_EQUAL(browser.getWindows().size(), 1);
    ASSERT_EQUAL(browser.getWindow(0)->getUrl(), "http://localhost:4567/simple.xml");
  }

  void testEnabledCookiesHandling()
  {
    Browser browser;
    browser.enableCookies();
    browser.open("http://localhost:4567/cookies/set");
    Page* page = browser.open("http://localhost:4567/cookies/show");
    ASSERT_EQUAL(page->getContent(), "foo=foobar");
  }

  void testDisabledCookiesHandling()
  {
    Browser browser;
    browser.disableCookies();
    browser.open("http://localhost:4567/cookies/set");
    Page* page = browser.open("http://localhost:4567/cookies/show");
    ASSERT_EQUAL(page->getContent(), "foo=");
  }

  void testWorkOnLineAndOffLine()
  {
    Browser browser;
    ASSERT(browser.isOnLine());
    browser.workOffLine();
    ASSERT_NOT(browser.isOnLine());
    browser.workOnLine();
    ASSERT(browser.isOnLine());
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeBrowserTest);

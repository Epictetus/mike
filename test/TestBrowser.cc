#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "Browser.h"
#include "Window.h"
#include "Page.h"
#include "utils/SystemInfo.h"

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
  CPPUNIT_TEST_SUITE_END();

protected:

  void testLanguage()
  {
    Browser* browser = new Browser();
    ASSERT_EQUAL(browser->getLanguage(), "en");
    browser = new Browser("pl");
    ASSERT_EQUAL(browser->getLanguage(), "pl");
    delete browser;
  }

  void testDefaultUserAgent()
  {
    Browser* browser = new Browser();
    ASSERT_EQUAL(browser->getUserAgent(), "Mozilla/5.0 (Memory; " + string(OS_TYPE) + " " + string(CPU_ARCH)+") Mike/" + string(MIKE_VERSION) + " (Mike, like Gecko) Mike/1");
    delete browser;
  }

  void testCustomUserAgent()
  {
    Browser* browser = new Browser("en", "my user agent string");
    ASSERT_EQUAL(browser->getUserAgent(), "my user agent string");
    delete browser;
  }

  void testIsJavaEnabled()
  {
    Browser* browser = new Browser();
    ASSERT_EQUAL(browser->isJavaEnabled(), true);
    ASSERT_EQUAL(browser->isJavaScriptEnabled(), true);
    browser = new Browser("en", "", true, false);
    ASSERT_EQUAL(browser->isJavaEnabled(), false);
    delete browser;
  }

  void testIsCookieEnabled()
  {
    Browser* browser = new Browser();
    ASSERT_EQUAL(browser->isCookieEnabled(), true);
    browser = new Browser("en", "", false);
    ASSERT_EQUAL(browser->isCookieEnabled(), false);
    delete browser;
  }

  void testOpen()
  {
    Browser* browser = new Browser();
    Page* page = browser->open("http://localhost:4567/simple");
    ASSERT_NOT_NULL(page);
    ASSERT_EQUAL(page->getContent(), "Kukuryku!");
    delete browser;
  }

  void testGetWindows()
  {
    Browser* browser = new Browser();
    browser->open("http://localhost:4567/simple.html");
    browser->open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser->getWindows().size(), 2);
    delete browser;
  }

  void testGetWindow()
  {
    Browser* browser = new Browser();
    browser->open("http://localhost:4567/simple.html");
    browser->open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser->getWindow(1)->getUrl(), "http://localhost:4567/simple.xml");
    ASSERT_NULL(browser->getWindow(2));
    delete browser;
  }

  void testCloseAll()
  {
    Browser* browser = new Browser();
    browser->open("http://localhost:4567/simple.html");
    browser->open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser->getWindows().size(), 2);
    browser->closeAll();
    ASSERT_EQUAL(browser->getWindows().size(), 0);
    delete browser;
  }

  void testCloseWindowByPosition()
  {
    Browser* browser = new Browser();
    browser->open("http://localhost:4567/simple.html");
    browser->open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser->getWindows().size(), 2);
    browser->closeWindow(0);
    ASSERT_EQUAL(browser->getWindows().size(), 1);
    ASSERT_EQUAL(browser->getWindow(0)->getUrl(), "http://localhost:4567/simple.xml");
    delete browser;
  }

  void testCloseWindowByObject()
  {
    Browser* browser = new Browser();
    browser->open("http://localhost:4567/simple.html");
    browser->open("http://localhost:4567/simple.xml");
    ASSERT_EQUAL(browser->getWindows().size(), 2);
    browser->closeWindow(browser->getWindow(0));
    ASSERT_EQUAL(browser->getWindows().size(), 1);
    ASSERT_EQUAL(browser->getWindow(0)->getUrl(), "http://localhost:4567/simple.xml");
    delete browser;
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeBrowserTest);

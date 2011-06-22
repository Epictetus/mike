#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "Browser.h"
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
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeBrowserTest);

#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "Browser.h"
#include "Window.h"

using namespace std;
using namespace mike;

class MikeWindowTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeWindowTest);
  CPPUNIT_TEST(testGetBrowser);
  CPPUNIT_TEST(testGetBrowserWhenParentWindowGiven);
  CPPUNIT_TEST(testGetParentWindow);
  CPPUNIT_TEST(testGetTopLevelWindow);
  CPPUNIT_TEST(testGetUrl);
  CPPUNIT_TEST(testGetTitle);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testGetBrowser()
  {
    Browser* browser = new Browser();
    Window* window = new Window(browser, "http://localhost:4567/simple.html");
    ASSERT_EQUAL(window->getBrowser(), browser);
    delete window;
    delete browser;
  }

  void testGetBrowserWhenParentWindowGiven()
  {
    Browser* browser = new Browser();
    Window* parentWindow = new Window(browser, "http://localhost:4567/simple.html");
    Window* childWindow = new Window(parentWindow, "http://localhost:4567/simple.html");
    ASSERT_EQUAL(childWindow->getBrowser(), browser);
    delete parentWindow;
    delete childWindow;
    delete browser;    
  }

  void testGetParentWindow()
  {
    Browser* browser = new Browser();
    Window* parentWindow = new Window(browser, "http://localhost:4567/simple.html");
    Window* childWindow = new Window(parentWindow, "http://localhost:4567/simple.html");
    ASSERT_EQUAL(childWindow->getParentWindow(), parentWindow);
    ASSERT_EQUAL(parentWindow->getParentWindow(), parentWindow);
    delete parentWindow;
    delete childWindow;
    delete browser;
  }

  void testGetTopLevelWindow()
  {
    Browser* browser = new Browser();
    Window* topLevelWindow = new Window(browser, "http://localhost:4567/simple.html");
    Window* parentWindow = new Window(topLevelWindow, "http://localhost:4567/simple.html");
    Window* childWindow = new Window(parentWindow, "http://localhost:4567/simple.html");
    ASSERT_EQUAL(childWindow->getTopLevelWindow(), topLevelWindow);
    ASSERT_EQUAL(parentWindow->getTopLevelWindow(), topLevelWindow);
    ASSERT_EQUAL(topLevelWindow->getTopLevelWindow(), topLevelWindow);
    delete topLevelWindow;
    delete parentWindow;
    delete childWindow;
    delete browser;
  }

  void testGetUrl()
  {
    Browser* browser = new Browser();
    string url = "http://localhost:4567/simple.html";
    Window* window = browser->Open(url);
    ASSERT_EQUAL(window->getUrl(), url);
    delete browser;
  }

  void testGetTitle()
  {
    Browser* browser = new Browser();
    Window* window1 = browser->Open("http://localhost:4567/simple.html");
    Window* window2 = browser->Open("http://localhost:4567/simple.xml");
    Window* window3 = browser->Open("http://localhost:4567/with-title.html");
    Window* window4 = browser->Open("about:blank");
    ASSERT_EQUAL(window1->getTitle(), "http://localhost:4567/simple.html");
    ASSERT_EQUAL(window2->getTitle(), "http://localhost:4567/simple.xml");
    ASSERT_EQUAL(window3->getTitle(), "Hello World!");
    ASSERT_EQUAL(window4->getTitle(), "Blank...");
    delete browser;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeWindowTest);

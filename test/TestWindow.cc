#include "test/Macros.h"

#include "Browser.h"
#include "Window.h"
#include "Frame.h"
#include "Page.h"

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
  CPPUNIT_TEST(testIsBlank);
  CPPUNIT_TEST(testGetPage);
  CPPUNIT_TEST(testDefaultSize);
  CPPUNIT_TEST(testResize);
  CPPUNIT_TEST(testClose);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testGetBrowser()
  {
    Browser* browser = new Browser();
    Window* window = new Window(browser);
    ASSERT_EQUAL(window->getBrowser(), browser);
    delete window;
    delete browser;
  }

  void testGetBrowserWhenParentWindowGiven()
  {
    Browser* browser = new Browser();
    Window* parent = new Window(browser);
    Window* child = new Window(parent);
    ASSERT_EQUAL(child->getBrowser(), browser);
    delete parent;
    delete child;
    delete browser;
  }

  void testGetParentWindow()
  {
    Browser* browser = new Browser();
    Window* parent = new Window(browser);
    Window* child = new Window(parent);
    ASSERT_EQUAL(child->getParent(), parent);
    ASSERT_EQUAL(parent->getParent(), parent);
    delete parent;
    delete child;
    delete browser;
  }

  void testGetTopLevelWindow()
  {
    Browser* browser = new Browser();
    Window* top = new Window(browser);
    Window* parent = new Window(top);
    Window* child = new Window(parent);
    ASSERT_EQUAL(child->getTopLevel(), top);
    ASSERT_EQUAL(parent->getTopLevel(), top);
    ASSERT_EQUAL(top->getTopLevel(), top);
    delete top;
    delete parent;
    delete child;
    delete browser;
  }

  void testGetUrl()
  {
    Browser* browser = new Browser();
    string url = "http://localhost:4567/simple.html";
    Window* window = new Window(browser);
    window->setPage(Page::Open(url));
    ASSERT_EQUAL(window->getUrl(), url);
    delete window;
    delete browser;
  }

  void testIsBlank()
  {
    Browser* browser = new Browser();
    Window* window = new Window(browser);
    ASSERT(window->isBlank());
    window->setPage(Page::Open("http://localhost:4567/simple"));
    ASSERT_NOT(window->isBlank());
    delete window;
    delete browser;
  }

  void testGetPage()
  {
    Browser* browser = new Browser();
    Window* window = new Window(browser);
    Page* page = Page::Open("http://localhost:4567/simple");
    window->setPage(page);
    ASSERT_EQUAL(window->getPage(), page);
    delete window;
    delete browser;
  }

  void testDefaultSize()
  {
    Browser* browser = new Browser();
    Window* window = new Window(browser);
    ASSERT_EQUAL(window->getWidth(), 1280);
    ASSERT_EQUAL(window->getHeight(), 1024);
    delete window;
    delete browser;
  }

  void testResize()
  {
    Browser* browser = new Browser();
    Window* window = new Window(browser);
    window->resizeX(800);
    ASSERT_EQUAL(window->getWidth(), 800);
    ASSERT_EQUAL(window->getHeight(), 1024);
    window->resizeY(600);
    ASSERT_EQUAL(window->getWidth(), 800);
    ASSERT_EQUAL(window->getHeight(), 600);
    window->resize(1600, 1200);
    ASSERT_EQUAL(window->getWidth(), 1600);
    ASSERT_EQUAL(window->getHeight(), 1200);
    delete window;
    delete browser;
  }

  void testClose()
  {
    Browser* browser = new Browser();
    browser->open("http://localhost:4567/simple");
    Window* window = browser->getWindow(0);
    window->close();
    ASSERT_EQUAL(browser->getWindows().size(), 0);
    delete browser;
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeWindowTest);

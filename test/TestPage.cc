#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "Page.h"
#include "Browser.h"
#include "Window.h"
#include "Frame.h"

using namespace std;
using namespace mike;
using namespace mike::http;

class MikePageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikePageTest);
  CPPUNIT_TEST(testOpen);
  CPPUNIT_TEST(testFactoryWhenInvalidUrlGiven);
  CPPUNIT_TEST(testGetContent);
  CPPUNIT_TEST(testGetUrl);
  CPPUNIT_TEST(testGetStream);
  CPPUNIT_TEST(testGetEnclosingFrame);
  CPPUNIT_TEST(testMultipleEncloseProtection);
  CPPUNIT_TEST(testGetEnclosingWindow);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testOpen()
  {
    Page* page = Page::Open("http://localhost:4567/simple");
    ASSERT_EQUAL(page->getContent(), "Kukuryku!");
    delete page;
  }
  
  void testFactoryWhenInvalidUrlGiven()
  {
    Request* request = Request::Get("http://thiswebsiteforsure/not/exists");
    ASSERT_THROW(Page::Factory(request), ConnectionError);
  }

  void testGetContent()
  {
    Page* page = Page::Open("http://localhost:4567/simple.txt");
    ASSERT_EQUAL(page->getContent(), "Simple!");
    delete page;
  }

  void testGetUrl()
  {
    Page* page = Page::Open("http://localhost:4567/simple.txt");
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple.txt");
    delete page;
  }
  
  void testGetStream()
  {
    Page* page = Page::Open("http://localhost:4567/simple.txt");;
    ASSERT_NOT_NULL(page->getStream());
    ASSERT_EQUAL(page->getStream()->str(), "Simple!");
    delete page;
  }

  void testGetEnclosingFrame()
  {
    Frame* frame = new Frame();
    Page* page = Page::Open("http://localhost:4567/simple.txt");
    page->enclose(frame);
    ASSERT_EQUAL(page->getEnclosingFrame(), frame);
    delete frame;
  }

  void testMultipleEncloseProtection()
  {
    Frame* frame1 = new Frame();
    Frame* frame2 = new Frame();
    Page* page = Page::Open("http://localhost:4567/simple.txt");
    page->enclose(frame1);
    page->enclose(frame2);
    ASSERT_EQUAL(page->getEnclosingFrame(), frame1);
    delete frame1;
    delete frame2;
  }

  void testGetEnclosingWindow()
  {
    Browser* browser = new Browser();
    Window* window = new Window(browser);
    Frame* frame = new Frame(window);
    Page* page = Page::Open("http://localhost:4567/simple.txt");
    page->enclose(frame);
    ASSERT_EQUAL(page->getEnclosingWindow(), window);
    delete frame;
    delete window;
    delete browser;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(MikePageTest);

#include "test/Macros.h"
#include <time.h>

#include "History.h"
#include "Page.h"

using namespace std;
using namespace mike;

class MikeHistoryTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeHistoryTest);
  CPPUNIT_TEST(testPushing);
  CPPUNIT_TEST(testGoBack);
  CPPUNIT_TEST(testGoForward);
  CPPUNIT_TEST(testGo);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testPushing()
  {
    Page* page1 = Page::Open("http://localhost:4567/simple.xml");
    Page* page2 = Page::Open("http://localhost:4567/simple.html");
    History* history = new History();
    history->push(page1);
    ASSERT_EQUAL(history->size(), 0);
    ASSERT_EQUAL(history->getCurrent(), page1);
    history->push(page2);
    ASSERT_EQUAL(history->size(), 1);
    ASSERT_EQUAL(history->getCurrent(), page2);
    delete history;
  }

  void testGoBack()
  {
    History* history = new History();
    Page* pages[4];
    
    for (int i = 0; i < 4; i++) {
      pages[i] = Page::Open("http://localhost:4567/simple");
      history->push(pages[i]);
    }

    ASSERT_EQUAL(history->size(), 3);
    ASSERT_EQUAL(history->getCurrent(), pages[3]);
    
    history->goBack();
    ASSERT_EQUAL(history->size(), 3);
    ASSERT_EQUAL(history->getCurrent(), pages[2]);

    for (int i = 0; i < 10; i++) {
      history->goBack();
    }

    ASSERT_EQUAL(history->getCurrent(), pages[0]);
    
    delete history;
  }

  void testGoForward()
  {
    History* history = new History();
    Page* pages[4];
    
    for (int i = 0; i < 4; i++) {
      pages[i] = Page::Open("http://localhost:4567/simple");
      history->push(pages[i]);
    }

    history->goBack();
    history->goBack();
    ASSERT_EQUAL(history->getCurrent(), pages[1]);

    history->goForward();
    ASSERT_EQUAL(history->getCurrent(), pages[2]);
    
    for (int i = 0; i < 10; i++) {
      history->goForward();
    }
    
    ASSERT_EQUAL(history->getCurrent(), pages[3]);

    delete history;
  }

  void testGo()
  {
    History* history = new History();
    Page* pages[4];
    
    for (int i = 0; i < 4; i++) {
      pages[i] = Page::Open("http://localhost:4567/simple");
      history->push(pages[i]);
    }

    history->go(-2);
    ASSERT_EQUAL(history->getCurrent(), pages[1]);
    history->go(1);
    ASSERT_EQUAL(history->getCurrent(), pages[2]);
    history->go(0);
    ASSERT_EQUAL(history->getCurrent(), pages[2]);
    history->go(10);
    ASSERT_EQUAL(history->getCurrent(), pages[3]);
    history->go(-20);
    ASSERT_EQUAL(history->getCurrent(), pages[0]);
    history->go(-10);
    ASSERT_EQUAL(history->getCurrent(), pages[0]);
    
    delete history;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHistoryTest);

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>
#include <time.h>

#include "utils/CppunitMacros.h"
#include "History.h"

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
    http::Request* request1 = http::Request::Get("http://localhost:4567/simple");
    Page* page1 = Page::Build(request1);
    http::Request* request2 = http::Request::Get("http://localhost:4567/simple");
    Page* page2 = Page::Build(request2);
    History* history = new History();
    history->push(page1);
    ASSERT_EQUAL(history->size(), 0);
    ASSERT_EQUAL(history->getCurrent(), page1);
    history->push(page2);
    ASSERT_EQUAL(history->size(), 1);
    delete history;
  }

  void testGoBack()
  {
    History* history = new History();
    Page* pages[4];
    
    for (int i = 0; i < 4; i++) {
      http::Request* request = http::Request::Get("http://localhost:4567/simple");
      pages[i] = Page::Build(request);
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
      http::Request* request = http::Request::Get("http://localhost:4567/simple");
      pages[i] = Page::Build(request);
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
      http::Request* request = http::Request::Get("http://localhost:4567/simple");
      pages[i] = Page::Build(request);
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

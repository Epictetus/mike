#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "mike/utils/test.h"
#include "mike/page.h"

using namespace std;
using namespace mike;

class MikePageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikePageTest);
  CPPUNIT_TEST(createTest);
  CPPUNIT_TEST(bodyWhilePageNotLoadedTest);
  CPPUNIT_TEST(loadTest);
  CPPUNIT_TEST(htmlDocumentTest);
  CPPUNIT_TEST_SUITE_END();
protected:
  void createTest();
  void bodyWhilePageNotLoadedTest();
  void loadTest();
  void htmlDocumentTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikePageTest);

void MikePageTest::createTest()
{
  string url = "http://localhost:4567/simple";
  Page *page = new Page(NULL, url, "GET");
  ASSERT_EQUAL(page->Url(), url);
  ASSERT_EQUAL(page->Request()->Method(), "GET");
  delete page;
}

void MikePageTest::bodyWhilePageNotLoadedTest()
{
  Page *page = new Page(NULL, "http://localhost:4567/simple");
  ASSERT_THROW(page->Body(), PageNotLoadedError);
  delete page;
}

void MikePageTest::loadTest()
{
  Page *page = new Page(NULL, "http://localhost:4567/simple");
  ASSERT_NOT(page->IsLoaded());
  page->Load();
  ASSERT(page->IsLoaded());
  ASSERT_EQUAL(page->Body(), "Kukuryku!");
  delete page;
}

void MikePageTest::htmlDocumentTest()
{
  Page *page = new Page(NULL, "http://localhost:4567/simple.html");
  page->Load();
  ASSERT(page->IsLoaded());
  ASSERT_EQUAL(page->Body(), "<html><body>Simple!</body></html>");
  ASSERT_NOT_NULL(page->Document());
  delete page;
}

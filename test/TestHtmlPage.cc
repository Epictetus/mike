#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "html/HtmlPage.h"

using namespace std;
using namespace mike;

class MikeHtmlPageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeHtmlPageTest);
  CPPUNIT_TEST(testBuild);
  CPPUNIT_TEST(testGetElementsByTagName);
  CPPUNIT_TEST(testGetElementsByXpath);
  CPPUNIT_TEST(testGetElementsById);
  CPPUNIT_TEST(testGetElementsByClassName);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuild()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/simple");
    Page* page = Page::Build(request);
    ASSERT(page && page->isLoaded());
    ASSERT_EQUAL(page->getUrl(), "http://localhost:4567/simple");
    ASSERT(page->isHtml());
    ASSERT(page->toHtmlPage());
    delete page;
  }

  void testGetElementsByTagName()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xpath.html");
    HtmlPage* page = Page::Build(request)->toHtmlPage();
    ASSERT(page && page->isLoaded());
    vector<XmlElement*> elems = page->getElementsByTagName("li");
    ASSERT_EQUAL(elems.size(), 3);
    elems.clear();
    delete page;
  }
  
  void testGetElementsByXpath()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xpath.html");
    HtmlPage* page = Page::Build(request)->toHtmlPage();
    ASSERT(page && page->isLoaded());
    vector<XmlElement*> elems = page->getElementsByXpath("//ul[@id='elems']/li[contains(@class, 'load')]");
    ASSERT_EQUAL(elems.size(), 2);
    elems.clear();
    delete page;
  }

  void testGetElementsById()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xpath.html");
    HtmlPage* page = Page::Build(request)->toHtmlPage();
    ASSERT(page && page->isLoaded());
    XmlElement* should_be_found = page->getElementById("elems");
    XmlElement* should_not_be_found = page->getElementById("not-found");
    ASSERT_NOT_NULL(should_be_found);
    ASSERT_NULL(should_not_be_found);
    delete should_be_found;
    delete should_not_be_found;
    delete page;
  }

  void testGetElementsByClassName()
  {
    http::Request* request = http::Request::Get("http://localhost:4567/xpath.html");
    HtmlPage* page = Page::Build(request)->toHtmlPage();
    ASSERT(page && page->isLoaded());
    vector<XmlElement*> elems_ok = page->getElementsByClassName("load");
    vector<XmlElement*> elems_not_ok = page->getElementsByClassName("loa");
    vector<XmlElement*> elems_not_ok_too = page->getElementsByClassName("load fo");
    ASSERT_EQUAL(elems_ok.size(), 2);
    ASSERT_EQUAL(elems_not_ok.size(), 0);
    ASSERT_EQUAL(elems_not_ok_too.size(), 0);
    elems_ok.clear();
    elems_not_ok.clear();
    elems_not_ok_too.clear();
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHtmlPageTest);

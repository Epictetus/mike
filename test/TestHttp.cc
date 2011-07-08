#include "test/Macros.h"

#include "http/Request.h"

using namespace std;
using namespace mike;
using namespace mike::http;

class MikeHttpTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeHttpTest);
  CPPUNIT_TEST(testInitAttributesForGetRequest);
  CPPUNIT_TEST(testInitAttributesForPostRequest);
  CPPUNIT_TEST(testSimpleGet);
  CPPUNIT_TEST(testGetWithCustomHeaders);
  CPPUNIT_TEST(testErrorResponseCode);
  CPPUNIT_TEST(testFollowRedirects);
  CPPUNIT_TEST(testSimplePost);
  CPPUNIT_TEST(testContentType);
  CPPUNIT_TEST(testIsHtmlMethod);
  CPPUNIT_TEST(testIsXmlMethod);
  CPPUNIT_TEST(testCookiesWhenEnabled);
  CPPUNIT_TEST(testCookiesWhenDisabled);
  CPPUNIT_TEST(testHttpAuth);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testInitAttributesForGetRequest()
  {
    Request *req = Request::Get("http://localhost:4567/simple");
    ASSERT_EQUAL(req->getUrl(), "http://localhost:4567/simple");
    ASSERT_EQUAL(req->getMethod(), "GET");
    delete req;
  }

  void testInitAttributesForPostRequest()
  {
    Request *req = Request::Post("http://localhost:4567/simple");
    ASSERT_EQUAL(req->getUrl(), "http://localhost:4567/simple");
    ASSERT_EQUAL(req->getMethod(), "POST");
    delete req;
  }

  void testSimpleGet()
  {
    Request *req = Request::Get("http://localhost:4567/simple");
    req->perform();
    ASSERT_EQUAL(req->getResponse()->getUrl(), "http://localhost:4567/simple");
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    ASSERT_EQUAL(req->getResponse()->getHeader("Content-Type"), "text/html;charset=utf-8");
    ASSERT_EQUAL(req->getResponse()->getHeader("No-Such-Header"), "");
    ASSERT_EQUAL(req->getResponse()->getBody(), "Kukuryku!");
    delete req;
  }

  void testGetWithCustomHeaders()
  {
    Request *req = Request::Get("http://localhost:4567/custom-headers");
    req->setHeader("Accept: chickens");
    req->setHeader("Another: kukuryku");
    req->perform();
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    ASSERT_EQUAL(req->getResponse()->getBody(), "Accept: chickens; Another: kukuryku;");
    delete req;
  }

  void testErrorResponseCode()
  {
    Request *req = Request::Get("http://localhost:4567/not-exists");
    req->perform();
    ASSERT_EQUAL(req->getResponse()->getCode(),404);
    delete req;
  }

  void testFollowRedirects()
  {
    Request *req = Request::Get("http://localhost:4567/follow-redirects");
    req->perform();
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    ASSERT_EQUAL(req->getResponse()->getBody(), "Redirected!");
    delete req;
  }

  void testSimplePost()
  {
    Request *req = Request::Post("http://localhost:4567/simple");
    req->setData("mike=kukuryku&foo=bar");
    req->perform();
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    ASSERT_EQUAL(req->getResponse()->getBody(), "mike: kukuryku; foo: bar;");
    delete req;
  }

  void testContentType()
  {
    Request *req = Request::Get("http://localhost:4567/simple");
    req->perform();
    ASSERT_EQUAL(req->getResponse()->getContentType(), "text/html");
    delete req;
  }

  void testIsHtmlMethod()
  {
    Request *req = Request::Get("http://localhost:4567/simple");
    req->perform();
    ASSERT(req->getResponse()->isHtml());
    delete req;
  }

  void testIsXmlMethod()
  {
    Request *req = Request::Get("http://localhost:4567/simple.xml");
    req->perform();
    ASSERT(req->getResponse()->isXml());
    delete req;
  }

  void testCookiesWhenEnabled()
  {
    string token = "test";
    Request *set = Request::Get("http://localhost:4567/cookies/set");
    set->enableCookieSession(token);
    set->perform();
    Request *show = Request::Get("http://localhost:4567/cookies/show");
    show->enableCookieSession(token);
    show->perform();
    ASSERT_EQUAL(show->getResponse()->getBody(), "foo=foobar");
    delete set;
    delete show;
  }

  void testCookiesWhenDisabled()
  {
    Request *set = Request::Get("http://localhost:4567/cookies/set");
    set->perform();
    Request *show = Request::Get("http://localhost:4567/cookies/show");
    show->perform();
    ASSERT_EQUAL(show->getResponse()->getBody(), "foo=");
    delete set;
    delete show;
  }

  void testHttpAuth()
  {
    Request *req = Request::Get("http://user:pass@localhost:4567/protected.html");
    req->perform();
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    delete req;
    req = Request::Get("http://user:failpass@localhost:4567/protected.html");
    req->perform();
    ASSERT_EQUAL(req->getResponse()->getCode(), 401);
    delete req;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHttpTest);

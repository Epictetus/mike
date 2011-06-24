#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "utils/CppunitMacros.h"
#include "http/Request.h"

using namespace std;
using namespace mike;

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
  CPPUNIT_TEST(testCookies);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testInitAttributesForGetRequest()
  {
    http::Request *req = http::Request::Get("http://localhost:4567/simple");
    ASSERT_EQUAL(req->getUrl(), "http://localhost:4567/simple");
    ASSERT_EQUAL(req->getMethod(), "GET");
    delete req;
  }

  void testInitAttributesForPostRequest()
  {
    http::Request *req = http::Request::Post("http://localhost:4567/simple");
    ASSERT_EQUAL(req->getUrl(), "http://localhost:4567/simple");
    ASSERT_EQUAL(req->getMethod(), "POST");
    delete req;
  }

  void testSimpleGet()
  {
    http::Request *req = http::Request::Get("http://localhost:4567/simple");
    ASSERT(req->perform());
    ASSERT(req->isReady());
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    ASSERT_EQUAL(req->getResponse()->getHeader("Content-Type"), "text/html;charset=utf-8");
    ASSERT_EQUAL(req->getResponse()->getHeader("No-Such-Header"), "");
    ASSERT_EQUAL(req->getResponse()->getBody(), "Kukuryku!");
    delete req;
  }

  void testGetWithCustomHeaders()
  {
    http::Request *req = http::Request::Get("http://localhost:4567/custom-headers");
    req->setHeader("Accept: chickens");
    req->setHeader("Another: kukuryku");
    ASSERT(req->perform());
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    ASSERT_EQUAL(req->getResponse()->getBody(), "Accept: chickens; Another: kukuryku;");
    delete req;
  }

  void testErrorResponseCode()
  {
    http::Request *req = http::Request::Get("http://localhost:4567/not-exists");
    ASSERT(req->perform());
    ASSERT_EQUAL(req->getResponse()->getCode(),404);
    delete req;
  }

  void testFollowRedirects()
  {
    http::Request *req = http::Request::Get("http://localhost:4567/follow-redirects");
    ASSERT(req->perform());
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    ASSERT_EQUAL(req->getResponse()->getBody(), "Redirected!");
    delete req;
  }

  void testSimplePost()
  {
    http::Request *req = http::Request::Post("http://localhost:4567/simple");
    req->setData("mike=kukuryku&foo=bar");
    ASSERT(req->perform());
    ASSERT_EQUAL(req->getResponse()->getCode(), 200);
    ASSERT_EQUAL(req->getResponse()->getBody(), "mike: kukuryku; foo: bar;");
    delete req;
  }

  void testContentType()
  {
    http::Request *req = http::Request::Get("http://localhost:4567/simple");
    ASSERT(req->perform());
    ASSERT_EQUAL(req->getResponse()->getContentType(), "text/html");
    delete req;
  }

  void testIsHtmlMethod()
  {
    http::Request *req = http::Request::Get("http://localhost:4567/simple");
    ASSERT(req->perform());
    ASSERT(req->getResponse()->isHtml());
    delete req;
  }

  void testIsXmlMethod()
  {
    http::Request *req = http::Request::Get("http://localhost:4567/simple.xml");
    ASSERT(req->perform());
    ASSERT(req->getResponse()->isXml());
    delete req;
  }

  void testCookies()
  {
    // TODO: add session tokens...
    http::Request *set = http::Request::Get("http://localhost:4567/cookies/set");
    ASSERT(set->perform());
    http::Request *show = http::Request::Get("http://localhost:4567/cookies/show");
    ASSERT(show->perform());
    ASSERT_EQUAL(show->getResponse()->getBody(), "foo=foobar");
    delete set;
    delete show;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHttpTest);

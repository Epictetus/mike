#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "mike/utils/http.h"

using namespace std;
using namespace mike;

class MikeUtilsHttpTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeUtilsHttpTest);
  CPPUNIT_TEST(initAttributesTest);
  CPPUNIT_TEST(simpleGetTest);
  CPPUNIT_TEST(getWithCustomHeadersTest);
  CPPUNIT_TEST(errorResponseCodeTest);
  CPPUNIT_TEST(followRedirectsTest);
  CPPUNIT_TEST(simplePostTest);
  CPPUNIT_TEST_SUITE_END();
protected:
  void initAttributesTest();
  void simpleGetTest();
  void getWithCustomHeadersTest();
  void errorResponseCodeTest();
  void followRedirectsTest();
  void simplePostTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeUtilsHttpTest);

void MikeUtilsHttpTest::initAttributesTest()
{
  http::Request *get = http::Request::GET("http://localhost:4567/simple");
  http::Request *post = http::Request::POST("http://localhost:4567/simple");
  CPPUNIT_ASSERT(get->Url() == "http://localhost:4567/simple");
  CPPUNIT_ASSERT(get->Method() == "GET");
  CPPUNIT_ASSERT(post->Method() == "POST");
  delete post;
  delete get;
}

void MikeUtilsHttpTest::simpleGetTest()
{
  http::Request *req = http::Request::GET("http://localhost:4567/simple");
  http::Response *res = req->Perform();
  CPPUNIT_ASSERT(res != NULL);
  CPPUNIT_ASSERT(res->Code() == 200);
  CPPUNIT_ASSERT(res->RawHeaders() != ""); // TODO: pending
  CPPUNIT_ASSERT(res->Body() != "Kukuryku!\n");
  delete req;
  delete res;
}

void MikeUtilsHttpTest::getWithCustomHeadersTest()
{
  http::Request *req = http::Request::GET("http://localhost:4567/custom-headers");
  req->SetHeader("Accept: chickens");
  req->SetHeader("Another: kukuryku");
  http::Response *res = req->Perform();
  CPPUNIT_ASSERT(res != NULL);
  CPPUNIT_ASSERT(res->Code() == 200);
  CPPUNIT_ASSERT(res->Body() == "Accept: chickens; Another: kukuryku;");
  delete req;
  delete res;
}

void MikeUtilsHttpTest::errorResponseCodeTest()
{
  http::Request *req = http::Request::GET("http://localhost:4567/not-exists");
  http::Response *res = req->Perform();
  CPPUNIT_ASSERT(res != NULL);
  CPPUNIT_ASSERT(res->Code() == 404);
  delete res;
  delete req;
}

void MikeUtilsHttpTest::followRedirectsTest()
{
  http::Request *req = http::Request::GET("http://localhost:4567/follow-redirects");
  http::Response *res = req->Perform();
  CPPUNIT_ASSERT(res != NULL);
  CPPUNIT_ASSERT(res->Code() == 200);
  CPPUNIT_ASSERT(res->Body() == "Redirected!");
  delete res;
  delete req;
}

void MikeUtilsHttpTest::simplePostTest()
{
  http::Request *req = http::Request::POST("http://localhost:4567/simple");
  req->SetData("mike=kukuryku&foo=bar");
  http::Response *res = req->Perform();
  CPPUNIT_ASSERT(res != NULL);
  CPPUNIT_ASSERT(res->Code() == 200);
  CPPUNIT_ASSERT(res->Body() == "mike: kukuryku; foo: bar;");
  delete res;
  delete req;
}

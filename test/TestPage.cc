#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "Page.h"

using namespace std;
using namespace mike;

class MikePageTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikePageTest);
  CPPUNIT_TEST(testBuildWhenInvalid);
  CPPUNIT_TEST_SUITE_END();

protected:

  void testBuildWhenInvalid()
  {
    http::Request* request = http::Request::Get("http://thiswebsiteforsure/not/exists");
    Page* page = Page::Build(request);
    ASSERT_NULL(page);
    delete page;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikePageTest);

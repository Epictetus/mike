#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "mike/config.h"
#include "mike/window.h"

using namespace std;
using namespace mike;

class MikeWindowTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeWindowTest);
  CPPUNIT_TEST(optionsTest);
  CPPUNIT_TEST(resizeTest);
  CPPUNIT_TEST_SUITE_END();
private:
  Window *window;
public:
  void setUp();
  void tearDown();
protected:
  void optionsTest();
  void resizeTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeWindowTest);

void MikeWindowTest::setUp()
{
  WindowOptions opts;
  opts.language = "pl";
  window = new Window(opts);
}

void MikeWindowTest::tearDown()
{
  delete window;
}

void MikeWindowTest::optionsTest()
{
  CPPUNIT_ASSERT(window->IsJavaEnabled());
  CPPUNIT_ASSERT(window->IsCookieEnabled());
  CPPUNIT_ASSERT(window->Language() == "pl");
  CPPUNIT_ASSERT(window->UserAgent() == "Mozilla/5.0 (Memory; "+string(OS_TYPE)+" "+string(CPU_ARCH)+") Mike/"+string(MIKE_VERSION)+" (Mike, like Gecko) Chrome/11 Safari/534.24");
  CPPUNIT_ASSERT(window->Width() == 1280);
  CPPUNIT_ASSERT(window->Height() == 1024);
}

void MikeWindowTest::resizeTest()
{
  window->ResizeX(640);
  CPPUNIT_ASSERT(window->Width() == 640);
  window->ResizeY(480);
  CPPUNIT_ASSERT(window->Height() == 480);
  window->Resize(800, 600);
  CPPUNIT_ASSERT(window->Width() == 800);
  CPPUNIT_ASSERT(window->Height() == 600);
}

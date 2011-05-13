#ifndef _MIKE_TEST_MACROS_H_
#define _MIKE_TEST_MACROS_H_

#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include "core/context.h"

namespace mike {
  namespace test
  {
    using namespace std;
    void assertJsEqual(context::Window* window, string js, v8::Handle<v8::Value> result);
  }
}

#define ASSERT(expr) CPPUNIT_ASSERT(expr)
#define ASSERT_JS_EQUAL(js, res) mike::test::assertJsEqual(window, js, res)

#endif /* _MIKE_TEST_MACROS_H_ */

#ifndef _MIKE_TEST_MACROS_H_
#define _MIKE_TEST_MACROS_H_

#include <cppunit/extensions/HelperMacros.h>

#define ASSERT(expr) CPPUNIT_ASSERT(expr)
#define ASSERT_JS_EQUAL(js, res) ASSERT(window->Evaluate(js)->result->Equals(res));

#endif /* _MIKE_TEST_MACROS_H_ */

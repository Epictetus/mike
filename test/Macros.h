#ifndef _TEST_MACROS_H_
#define _TEST_MACROS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <string.h>
#include <stdio.h>

#define ASSERT_MESSAGE(x, msg) CPPUNIT_ASSERT_MESSAGE(string(msg), x)

#ifndef CPPUNIT_ASSERT_THROW
#define CPPUNIT_ASSERT_THROW(expr, T)					\
  try {									\
    expr;								\
    ASSERT_MESSAGE(false, "#expr should throw #T exception");		\
  } catch (T err) {							\
  }
#endif

#define ASSERT(x) ASSERT_MESSAGE(x, "#x should be true")
#define ASSERT_NOT(x) ASSERT_MESSAGE(!x, "#x should be false")
#define ASSERT_EQUAL(x,y) ASSERT_MESSAGE(x == y, "#x should equals #y")
#define ASSERT_NOT_EQUAL(x,y) ASSERT_MESSAGE(x != y, "#x should not equals #y")
#define ASSERT_NULL(x) ASSERT_MESSAGE(x == NULL, "#x should be NULL")
#define ASSERT_NOT_NULL(x) ASSERT_MESSAGE(x != NULL, "#x should not be NULL")
#define ASSERT_STR_EQUAL(x,y) ASSERT_EQUAL(string(x), string(y))
#define ASSERT_STR_NOT_EQUAL(x,y) ASSERT_NOT_EQUAL(string(x), string(y))
#define ASSERT_THROW(e,t) CPPUNIT_ASSERT_THROW(e, t)

#endif /* _TEST_MACROS_H_ */

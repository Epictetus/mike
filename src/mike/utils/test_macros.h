#ifndef _MIKE_TEST_MACROS_H_
#define _MIKE_TEST_MACROS_H_

#ifdef CPPUNIT_ASSERT_THROW
#undef CPPUNIT_ASSERT_THROW
#endif

#define CPPUNIT_ASSERT_THROW(expr, errT)		\
  try {							\
    expr;						\
    CPPUNIT_ASSERT(false);				\
  } catch (errT err) {					\
    CPPUNIT_ASSERT(true);				\
  }

#define ASSERT(x) CPPUNIT_ASSERT(x)
#define ASSERT_NOT(x) ASSERT(!x)
#define ASSERT_EQUAL(x,y) ASSERT(x == y)
#define ASSERT_NOT_EQUAL(x,y) ASSERT(x != y)
#define ASSERT_NULL(x) ASSERT_EQUAL(x, NULL)
#define ASSERT_NOT_NULL(x) ASSERT_NOT_EQUAL(x, NULL)
#define ASSERT_STR_EQUAL(x,y) ASSERT_EQUAL(string(x),string(y))
#define ASSERT_STR_NOT_EQUAL(x,y) ASSERT_NOT_EQUAL(string(x),string(y))
#define ASSERT_THROW(e,t) CPPUNIT_ASSERT_THROW(e,t)

#endif /* _MIKE_TEST_MACROS_H_ */

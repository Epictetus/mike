#include "test/helpers.h"

namespace mike {
  namespace test
  {
    /*
     * Helper for testing javascript code within given window's context.
     * This function shouldn't be called directly, use <code>ASSERT_JS_EQUAL</code>
     * macro instead. 
     *
     */
    void assertJsEqual(context::Window* window, string js, v8::Handle<v8::Value> result)
    {
      v8::HandleScope scope;
      script::Info* info = window->Evaluate(js);
      CPPUNIT_ASSERT(info->error == script::seNone);
      CPPUNIT_ASSERT(info->result->Equals(result));
    }    
  }
}

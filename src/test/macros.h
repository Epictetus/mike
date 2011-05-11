#ifndef _MIKE_TEST_MACROS_H_
#define _MIKE_TEST_MACROS_H_

#include <cppunit/extensions/HelperMacros.h>
#include <v8.h>
#include <string>

namespace mike {
  namespace testhelpers {
    using namespace std;

    v8::Handle<v8::Value> compile_js(string jscode)
    {
      v8::HandleScope scope;
      v8::Local<v8::String> source = v8::String::New(jscode.c_str());
      v8::Local<v8::String> fname = v8::String::New("<test>");
      v8::Handle<v8::Script> script = v8::Script::Compile(source, fname);
      v8::Handle<v8::Value> result = script->Run();
      return result;
    }
  }
}

#define ASSERT(expr) CPPUNIT_ASSERT(expr)
#define ASSERT_V8_RESULT(jscode, expectation) \
  ASSERT(mike::testhelpers::compile_js(jscode)->Equals(expectation))


#endif /* _MIKE_TEST_MACROS_H_ */

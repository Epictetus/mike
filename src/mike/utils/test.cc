#include <stdio.h>
#include <stdlib.h>

#include "mike/utils/test.h"
#include "mike/utils/fs.h"

#include "mike/config.h"

namespace mike
{
  /**
   * Just displays error described by given exception and message passed
   * from the TryCatch object.
   *
   * @param kind: what kind of error we've got here
   * @param ex: exception value from try-catch
   * @param msg: message object from try-catch
   * @param fname: name of file where error appeared
   */
  void ReportError(string kind, Handle<Value> ex, Handle<Message> msg, string fname)
  {
    HandleScope scope;
    String::AsciiValue str(ex);
    printf("ERR/%s: %s in %s:%d\n", kind.c_str(), *str, fname.c_str(), msg->GetLineNumber());
  }

  /**
   * Loads given javascript file and evaluates it's content within currently
   * entered context. Returns true when given script's return value is not
   * empty, undefined or false.
   *
   * @param fname: name of file to evaluate
   */
  bool TestingEvalFile(string fname)
  {
    char *content = ReadFile(fname.c_str());

    if (content == NULL) {
      printf("ERR/Read: Cant read file %s\n", fname.c_str());
      return false;
    } else {
      return TestingEval(string(content), fname);
    }
  }

  /**
   * Evaluates given javascript source within currently entered context.
   * Returns true when given script's return value is not empty, undefined
   * or false.
   *
   * @param src: source to evaluate
   * @param fname: optional file name
   */
  bool TestingEval(string src, string fname/*="<eval>"*/)
  {
    HandleScope scope;
    bool result = false;
    
    if (!Context::InContext()) {
      printf("ERR/Context: Can't run test suite without entered context\n");
    } else {
      Handle<String> source = String::New(src.c_str());
      Handle<String> filename = String::New(fname.c_str());

      TryCatch try_catch;
      Handle<Script> script = Script::Compile(source, filename);

      if (try_catch.HasCaught()) {
	ReportError("Compile", try_catch.Exception(), try_catch.Message(), fname);
      } else {
	Handle<Value> res = script->Run();
      
	if (try_catch.HasCaught()) {
	  ReportError("Run", try_catch.Exception(), try_catch.Message(), fname);
	} else if (!res.IsEmpty()) {
	  result = res->ToBoolean()->BooleanValue();
	}
      }
    
      return result;
    }
  }
}

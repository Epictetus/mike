#ifndef _MIKE_CORE_SCRIPT_H_
#define _MIKE_CORE_SCRIPT_H_

#include <stdlib.h>
#include <string>
#include <v8.h>

namespace mike {
  namespace script
  {
    using namespace v8;
    using namespace std;

    /*
     * Short error codes for javascript execution. 
     * 
     */
    enum Error {
      seNone = 0,
      seCompileError = 1,
      seRuntimeError = 2
    };

    /*
     * This structure keeps information about executed script. It stores
     * persistent handle to result, raw source and file name and eventualy
     * error code.
     *
     */
    struct Info {
      string source;
      string name;
      Error error;
      Persistent<Value> result;
      Info(string source, string fname);
      virtual ~Info();
    };

    Info* Run(string source, string fname);
  }
}

#endif /* _MIKE_CORE_SCRIPT_H_ */

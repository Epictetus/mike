#include "mike/stdio.h"

namespace mike {
  namespace stdio
  {
    using namespace v8;
    
    /* 
     * Handler for javascript <code>$stdout.write</code> function.
     *
     */
    Handle<Value> WriteStdout(const Arguments &args)
    {
      HandleScope scope;
      
      if (args.Length() < 1) {
	return Undefined();
      }

      String::Utf8Value str(args[0]->ToString());
      printf("%s", *str);
      
      return True();
    }

    /* 
     * Handler for javascript <code>$stderr.write</code> function.
     *
     */
    Handle<Value> WriteStderr(const Arguments &args)
    {
      HandleScope scope;
      
      if (args.Length() < 1) {
	return Undefined();
      }

      String::Utf8Value str(args[0]->ToString());
      fprintf(stderr, "%s", *str);

      return True();
    }

    static char* ReadFileContent(char *fname)
    {
      FILE *fp = fopen(fname, "r");
      char *buffer;
      long lsize;

      if (fp != NULL) {
	fseek(fp, 0, SEEK_END);
	lsize = ftell(fp);
	rewind(fp);
	buffer = (char*)malloc((sizeof(char)*lsize));

	if (buffer == NULL || fread(buffer, 1, lsize, fp) != lsize) {
	  buffer = NULL;
	}

	fclose(fp);
      }

      return buffer;
    }
    
    /*
     * Handle for javascript <code>$io.read</code> function.
     *
     */
    Handle<Value> ReadFile(const Arguments &args)
    {
      HandleScope scope;
      
      if (args.Length() < 1) {
	return Undefined();
      }

      char *buffer;
      Handle<Value> res = False();
      String::Utf8Value fname(args[0]->ToString());

      if ((buffer = ReadFileContent(*fname)) != NULL) {
	res = Handle<Value>(String::New(buffer));
	free(buffer);
      }

      return res;
    }

    /*
     * Handle for javascript <code>$io.require</code> function.
     *
     */
    Handle<Value> RequireFile(const Arguments &args)
    {
      HandleScope scope;
      
      if (args.Length() < 1) {
	return Undefined();
      }

      char *buffer;
      Handle<Value> res = Undefined();
      String::Utf8Value fname(args[0]->ToString());

      if ((buffer = ReadFileContent(*fname)) != NULL) {
	Script *script = Script::Run(buffer, *fname);

	if (!script->HasErrors()) {
	  res = script->Result();
	}
	
	free(buffer);
      }

      return res;
    }
  }
}

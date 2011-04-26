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
      fprintf(stderr, "%s\n", *str);

      return True();
    }

    /*
     * Handle for javascript <code>$file.read</code> function.
     *
     */
    Handle<Value> ReadFile(const Arguments &args)
    {
      HandleScope scope;
      
      if (args.Length() < 1) {
	return Undefined();
      }

      Handle<Value> res = False();
      String::Utf8Value fname(args[0]->ToString());
      FILE *fp = fopen(*fname, "r");

      if (fp != NULL) {
	fseek(fp, 0, SEEK_END);
	long lsize = ftell(fp);
	rewind(fp);
	
	char *buffer;
	buffer = (char*)malloc((sizeof(char)*lsize));

	if (buffer != NULL && fread(buffer, 1, lsize, fp) == lsize) {
	  res = Handle<Value>(String::New(buffer));
	}

	free(buffer);
	fclose(fp);
      }

      return res;
    }
  }
}

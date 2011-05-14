#include "core/context.h"
#include "assert.h"
#include "unistd.h"

using namespace v8;
using namespace mike;
using namespace std;

int main(int argc, char **argv)
{
  HandleScope scope;
  context::Window *window = context::New();
  Handle<Value> result = window->Evaluate("$LOAD_PATH.push(System.pwd()+'/glue'); require('glue_suite');");
  assert(!result.IsEmpty());
  int failures = result->Int32Value();
  delete window;
  return failures;
}

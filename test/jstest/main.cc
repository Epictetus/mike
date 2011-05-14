#include <assert.h>
#include <unistd.h>
#include "core/context.h"

using namespace v8;
using namespace mike;
using namespace std;

int main(int argc, char **argv)
{
  HandleScope scope;
  context::Window *window = context::New();
  Handle<Value> result = window->Evaluate("$LOAD_PATH.push($mike.System.pwd()+'/jstest'); require('main');");
  assert(!result.IsEmpty());
  int failures = result->Int32Value();
  delete window;
  return failures;
}

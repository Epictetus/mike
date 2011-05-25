#ifndef _MIKE_UTILS_TEST_H_
#define _MIKE_UTILS_TEST_H_

#include <v8.h>
#include <string>

using namespace v8;
using namespace std;

namespace mike
{
  bool TestingEval(string src, string fname="<eval>");
  bool TestingEvalFile(string fname);
}

#endif /* _MIKE_UTILS_TEST_H_ */

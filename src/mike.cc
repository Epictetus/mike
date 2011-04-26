#include "mike.h"

namespace mike
{
  /*
   * Initializes mike's environment. 
   *
   */
  void Initialize()
  {
    v8::V8::Initialize();
  }

  /*
   * Disposes memory reserved by mike's environment. 
   *
   */
  void Dispose()
  {
    v8::V8::Dispose();
  }
}

#ifndef _MIKE_JAVASCRIPT_GLUE_OBJECT_H_
#define _MIKE_JAVASCRIPT_GLUE_OBJECT_H_

#include <string>
#include <v8.h>
#include <assert.h>

namespace mike {
  namespace glue
  {
    using namespace v8;
    using namespace std;

    class JsObject
    {
    public:
      template <typename T> static inline T* Unwrap(Handle<Object> handle, int field=0)
      {
	assert(!handle.IsEmpty());
	assert(handle->InternalFieldCount() > field);
	return (T*)handle->GetPointerFromInternalField(field);
      }
    };
  }
}

#endif /* _MIKE_JAVASCRIPT_GLUE_OBJECT_H_ */

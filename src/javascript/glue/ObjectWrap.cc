#include "javascript/glue/ObjectWrap.h"
#include "Window.h"

namespace mike {
  namespace glue
  {
    Window* ObjectWrap::GetWindow()
    {
      Handle<Object> global_proto = Handle<Object>::Cast(JS_GLOBAL->GetPrototype());
      return Unwrap<Window>(global_proto);
    }

    Handle<Value> ObjectWrap::Unwrap(Handle<Object> handle, int field/*=0*/)
    {
      assert(!handle.IsEmpty());
      assert(handle->InternalFieldCount() > field);
      return handle->GetInternalField(field);
    }

    void ObjectWrap::Wrap(Handle<Object> handle, Handle<Value> value, int field/*=0*/)
    {
      assert(!handle.IsEmpty());
      assert(handle->InternalFieldCount() > field);
      handle->SetInternalField(field, value);
    }
  }
}

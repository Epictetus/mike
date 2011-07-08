#ifndef _MIKE_JAVASCRIPT_OBJECT_WRAP_H_
#define _MIKE_JAVASCRIPT_OBJECT_WRAP_H_

#include <string>
#include <assert.h>
#include <v8.h>

namespace mike {
  namespace glue
  {
    using namespace v8;
    using namespace std;

    class ObjectWrap
    {
    public:
      /**
       * Unwraps external object of specified type from given handle's internal field.
       *
       * \param handle Handle to unwrap.
       * \param field Which field to pick up.
       * \return Unwrapped object.
       */
      template <typename T> static T* Unwrap(Handle<Object> handle, int field=0)
      {
	assert(!handle.IsEmpty());
	assert(handle->InternalFieldCount() > field);
	return (T*)External::Unwrap(handle->GetInternalField(1));
      }

      /**
       * Unwraps internal object type from given handle's internal field.
       *
       * \param handle Handle to unwrap.
       * \param field Which field to pick up.
       * \return Unwrapped handle.
       */
      static Handle<Value> Unwrap(Handle<Object> handle, int field=0);

      /**
       * Wraps given pointer within specified handle as an external object.
       *
       * \param handle Wrapper handle.
       * \param ptr Wrapped object.
       * \param field Which field to fill in.
       */
      template <typename T> static void Wrap(Handle<Object> handle, T* ptr, int field=0)
      {
        assert(!handle.IsEmpty());
        assert(handle->InternalFieldCount() > field);
        handle->SetInternalField(field, External::Wrap((void*)ptr));
      }

      /**
       * Wraps given internal object within specified handle.
       *
       * \param handle Wrapper handle.
       * \param value Wrapped object.
       * \param field Which field to fill in.
       */
      static void Wrap(Handle<Object> handle, Handle<Value> value, int field=0);
    };
  }
}

#endif /* _MIKE_JAVASCRIPT_OBJECT_WRAP_H_ */

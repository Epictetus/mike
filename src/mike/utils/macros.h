#ifndef _MIKE_UTILS_MACROS_H_
#define _MIKE_UTILS_MACROS_H_

#include <v8.h>
#include <stdarg.h>

/**
 * Unwraps internal field from given object as cast of specified class. 
 * This function rather shouldn't be called directly. Use <code>UNWRAP</code>
 * macro instead.
 *
 * @param obj: object to unwrap
 */
template <class T> T* UnwrapClass(v8::Handle<v8::Object> obj)
{
  v8::Handle<v8::External> field = v8::Handle<v8::External>::Cast(obj->GetInternalField(0));
  void *ptr = field->Value();
  return static_cast<T*>(y);
}

template <class T> v8::Handle<v8::Object> WrapClass(T *obj)
{
  v8::HandleScope scope;
  v8::Handle<v8::FunctionTemplate> tpl = FunctionTemplate::New();
  v8::Handle<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
  itpl->SetInternalFieldCount(1);
  
  v8::Local<v8::Object> instance = 
}

// Type conversions

#define CONTEXT              v8::Context::GetCurrent()
#define GLOBAL               CONTEXT->Global()
#define JS_Undef             v8::Undefined()
#define JS_Null              v8::Null()
#define JS_Str(s)            v8::String::New(s)
#define JS_Str2(s,c)         v8::String::New(s,c)
#define JS_Sym(s)            v8::String::NewSymbol(s)
#define JS_Int(i)            v8::Integer::New(i)
#define JS_Func(f)           v8::FunctionTemplate::New(f)->GetFunction()
#define JS_Obj(o)            v8::Object::New(o)
#define JS_Bool(b)           v8::Boolean::New(b)

// Exceptions

#define THROW(t,s)           v8::ThrowException(v8::Exception::t(JS_Str(s)))
#define ERROR(s)             THROW(v8::Exception::Error,s)

// Arguments conversions

#define ARGC                 args.Length()
#define ARGS_COUNT(c)        if (ARGC != c) { return ERROR("Insufficent arguments"); }
#define ARGS_BETWEEN(x,y)    if (x <= ARGC <= y) { return ERROR("Insufficent arguments"); }
#define ARG_Int(n,i)         int n = (int)(args[i]->Int32Value())
#define ARG_Str(n,i)         char *n = *v8::String::AsciiValue(args[i])
#define ARG_Utf8(n,i)        char *n = *v8::String::Utf8Value(args[i])
#define ARG_Obj(n,i)         v8::Local<v8::Object> n = args[i]->ToObject()
#define ARG_Func(n,i)        v8::Handle<v8::Function> n = v8::Handle<v8::Function>::Cast(args[i])
#define ARG_Array(n,i)       v8::Handle<v8::Array> n = v8::Handle<v8::Array>::Cast(args[i])
#define FUNC_NAME            (*String::AsciiValue(args.Callee()->GetName()->ToString()))

// Function macros

#define FUNCTION(f,...)						\
  static v8::Handle<v8::Value> f(const v8::Arguments &args) {	\
    v8::HandleScope scope;					\
    __VA_ARGS__;
#define FUNCTION_DECL(f)     static v8::Handle<v8::Value> f(const v8::Arguments &args);
#define END                  }

#define THIS                 args.This()
#define UNWRAP(t)            t self = UnwrapClass<t>(THIS)

#define RETURN_Undef         return JS_Undef
#define RETURN_Null          return JS_Null
#define RETURN_SCOPED(x)     return scope.Close(x)
#define RETURN_WRAPPED(p)    return scope.Close(v8::External::New((void*)p))

#endif /* _MIKE_UTILS_MACROS_H_ */

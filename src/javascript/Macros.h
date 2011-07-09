#ifndef _MIKE_JAVASCRIPT_MACROS_H_
#define _MIKE_JAVASCRIPT_MACROS_H_

#define JS_CONTEXT v8::Context::GetCurrent()
#define JS_GLOBAL JS_CONTEXT->Global()
#define JS_UNDEF v8::Undefined()
#define JS_NULL v8::Null()
#define JS_STR(s) v8::String::New(s)
#define JS_STR2(s,c) v8::String::New(s,c)
#define JS_SYM(s) v8::String::NewSymbol(s)
#define JS_INT(i) v8::Integer::New(i)
#define JS_FUNC_TPL(f) v8::FunctionTemplate::New(f)
#define JS_FUNC(f) JS_FUNC_TPL(f)->GetFunction()
#define JS_OBJ(o) v8::Object::New(o)
#define JS_BOOL(b) v8::Boolean::New(b)

#define JS_THROW_OBJ(obj) v8::ThrowException(obj)
#define JS_THROW(t,s) v8::ThrowException(v8::Exception::t(JS_Str(s)))
#define JS_ERROR(s) JS_THROW(v8::Exception::Error,s)

#define JS_ARGC args.Length()
#define JS_ARGS_COUNT(c) if (ARGC != c) { return ERROR("Insufficent arguments"); }
#define JS_ARGS_BETWEEN(x,y) if (x <= ARGC <= y) { return ERROR("Insufficent arguments"); }
#define JS_ARG_INT(n,i) int n = (int)(args[i]->Int32Value())
#define JS_ARG_STR(n,i) string n = string(*v8::String::AsciiValue(args[i]))
#define JS_ARG_UTF8(n,i) string n = string(*v8::String::Utf8Value(args[i]))
#define JS_ARG_OBJ(n,i) v8::Local<v8::Object> n = args[i]->ToObject()
#define JS_ARG_FUNC(n,i) v8::Handle<v8::Function> n = v8::Handle<v8::Function>::Cast(args[i])
#define JS_ARG_ARRAY(n,i) v8::Handle<v8::Array> n = v8::Handle<v8::Array>::Cast(args[i])
#define JS_FUNC_NAME (*String::AsciiValue(args.Callee()->GetName()->ToString()))

#define JS_GETTER_D(N)						         \
  static v8::Handle<Value> JS_Get##N(v8::Local<v8::String> property, 	 \
				     const v8::AccessorInfo& info);

#define JS_SETTER_D(N) \
  static v8::Handle<v8::Value> JS_Set##N(v8::Local<v8::String> property, \
					 v8::Local<v8::Value> value,	 \
					 const v8::AccessorInfo& info);

#define JS_FUNCTION_D(N)                                                 \
  static v8::Handle<v8::Value> JS_##N(const v8::Arguments& args);

#define JS_GETTER(obj,N,...)			  			 \
  v8::Handle<v8::Value> obj::JS_Get##N(v8::Local<v8::String> property,	 \
				       const v8::AccessorInfo& info)	 \
  {									 \
    v8::HandleScope scope;						 \
    __VA_ARGS__;

#define JS_SETTER(obj,N,...)						 \
  v8::Handle<v8::Value> obj::JS_Set##N(v8::Local<v8::String> property,	 \
				       v8::Local<v8::Value> value,	 \
				       const v8::AccessorInfo& info)	 \
  {									 \
    v8::HandleScope scope;						 \
    __VA_ARGS__;

#define JS_FUNCTION(obj,N,...)					         \
  v8::Handle<v8::Value> obj::JS_##N(const v8::Arguments& args)		 \
  {									 \
    v8::HandleScope scope;						 \
    __VA_ARGS__;

#define JS_END \
  }

#define JS_THIS args.This()
#define JS_HOLDER args.Holder()
#define JS_CALLEE args.Callee()
#define JS_UNWRAP(t) t self = Unwrap<t>(JS_THIS)
#define JS_UNWRAP_WINDOW UnwrapWindow(JS_HOLDER)

#define RETURN_SCOPED(x) scope.Close(x)
#define RETURN_WRAPPED(p) scope.Close(v8::External::New((void*)p))

#endif /* _MIKE_JAVASCRIPT_MACROS_H_ */

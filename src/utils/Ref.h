#ifndef _MIKE_REF_H_
#define _MIKE_REF_H_

namespace mike
{  
  template <typename T> class ref
  {
  public:
    ref(T* ptr)
    {
      ptr_ = ptr;
    }

    ~ref()
    {
      //if (T* tmp = ptr_)
	//ptr_->unref();
    }

    T* operator*()
    {
      return *ptr_;
    }
    
    T* operator->()
    {
      return ptr_;
    }

    template <typename U> inline ref<U>& operator()()
    {
      return ref<U>((U*)ptr_);
    }

    template <typename U> void up(U* ptr)
    {
      this = (T*)ptr;
    }

    inline ref<T>& operator=(T* optr)
    {
      //if (optr)
        //optr->mkref(&this);
      T* ptr = ptr_;
      ptr_ = optr;
      //if (ptr_)
        //ptr_->unref();
      return *this;
    }

    T* ptr_;
  };
}

#endif /* _MIKE_REF_H_ */

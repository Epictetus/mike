#ifndef _MIKE_PAGE_REF_H_
#define _MIKE_PAGE_REF_H_

#include "Page.h"
#include "Window.h"

namespace mike
{
  /**
   * Self-updating reference to page. It should be always used to keep reference to
   * pages opened in browser. Such reference will update automatically when new page is
   * being loaded.
   *
   * \code
   *   Browser* browser = new Browser()
   *   PageRef<HtmlPage> page = browser->open("http://cuboxsa.com/");
   *   page->click("Contact");
   *   assert(page->getUrl() == "http://cuboxsa.com/contact.html");
   * \endcode
   */
  template <typename T> class PageRef
  {
  public:
    /**
     * Creates empty reference;
     */
    PageRef();

    /**
     * Creates reference via window.
     *
     * \param window Window which contains referenced page.
     */
    PageRef(Window* window);

    /**
     * Creates reference directly from page.
     *
     * \param page Referenced page.
     */
    PageRef(T* page);

    /**
     * Destructor.
     */
    ~PageRef();

    /**
     * \return Whether reference is empty or not.
     */
    bool empty();
    
    /**
     * Assigns new reference via given page.
     *
     * \code
     *   PageRef<HtmlPage> page = browser->open("http://cuboxsa.com")
     *   page = browser->open("http://mikebrowser.com");
     *   assert(page->getUrl() == "http://mikebrowser.com");
     * \endcode
     *
     * \param page Referenced page.
     */
    PageRef<T>& operator=(T* page);

    /**
     * \return Pointer to referenced page.
     */
    T* operator->();

    /**
     * \return Referenced page object.
     */
    T operator*();

    /**
     * \return Referenced page casted to given pointer type.
     */
    template <typename U> operator U*();
    
    // Boolean operators
    bool operator!=(T* other);
    bool operator==(T* other);
    
  protected:
    Window* window_;
  };

  template <typename T> PageRef<T>::PageRef() {
    window_ = NULL;
  }
  
  template <typename T> PageRef<T>::PageRef(Window* window) {
    window_ = window;
  }

  template <typename T> PageRef<T>::PageRef(T* page) {
    window_ = page->getEnclosingWindow();
  }

  template <typename T> PageRef<T>::~PageRef() {
    window_ = NULL;
  }

  template <typename T> bool PageRef<T>::empty() {
    return window_ == NULL || window_->isBlank();
  }

  template <typename T> PageRef<T>& PageRef<T>::operator=(T* page) {
    if (page)
      window_ = page->getEnclosingWindow();
    else
      window_ = NULL;
    
    return *this;
  }

  template <typename T> T* PageRef<T>::operator->() {
    return empty() ? NULL : (T*)window_->getPage();
  }

  template <typename T> T PageRef<T>::operator*() {
    // XXX: possible segv, throw exception here?
    return *((T*)window_->getPage());
  }

  template <typename T> template<typename U> PageRef<T>::operator U*() {
    return empty() ? NULL : (U*)window_->getPage();
  }
  
  template <typename T> bool PageRef<T>::operator==(T* other) {
    return (T*)window_->getPage() == other;
  }

  template <typename T> bool PageRef<T>::operator!=(T* other) {
    return (T*)window_->getPage() != other;
  }  
}

#endif /* _MIKE_PAGE_REF_H_ */

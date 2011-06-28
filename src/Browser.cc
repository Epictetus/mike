#include <string.h>
#include <uuid/uuid.h>
#include "utils/SystemInfo.h"
#include "Page.h"
#include "Window.h"
#include "Browser.h"

namespace mike
{
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= LIFECYCLE ====================================

  Browser::Browser(string language/*="en"*/, string user_agent/*=""*/,
		   bool cookie_enabled/*=true*/, bool java_enabled/*=true*/)
    : language_(language)
    , customUserAgent_(user_agent)
    , cookieEnabled_(cookie_enabled)
    , javaEnabled_(java_enabled)
  {
    generateSessionToken();
  }

  Browser::~Browser()
  {
    closeAll();
  }

  //============================= ACCESS     ===================================

  string Browser::getLanguage() const
  {
    return language_;
  }

  string Browser::getUserAgent() const
  {
    if (customUserAgent_.empty()) {
      char* tpl = (char*)MIKE_USER_AGENT;
      char agent[255];
      sprintf(agent, tpl, OS_TYPE, CPU_ARCH, MIKE_VERSION);
      return agent;
    } else {
      return customUserAgent_;
    }
  }

  string Browser::getSessionToken() const
  {
    return sessionToken_;
  }
    
  bool Browser::isJavaEnabled() const
  {
    return javaEnabled_;
  }

  bool Browser::isJavaScriptEnabled() const
  {
    return isJavaEnabled();
  }

  bool Browser::isCookieEnabled() const
  {
    return cookieEnabled_;
  }

  // XXX: in the future it should return read only list...
  list<Window*> Browser::getWindows()
  {
    return windows_;
  }

  // XXX: should this raise exception when window is not found??
  Window* Browser::getWindow(int n)
  {
    if (n < windows_.size()) {
      list<Window*>::iterator it = windows_.begin();
      advance(it, n);
      return *it;
    }

    return NULL;
  }

  //============================= OPERATIONS ===================================

  Page* Browser::open(string url)
  {
    Window* window = new Window(this);
    windows_.push_back(window);

    Page* page = Page::Open(url);
    window->setPage(page);
    
    return page;
  }

  Page* Browser::getPage(string url)
  {
    open(url);
  }
  
  void Browser::closeAll()
  {
    for (list<Window*>::iterator it = windows_.begin(); it != windows_.end(); it++) {
      delete *it;
      *it = NULL;
    }

    windows_.clear();
  }

  void Browser::closeAllWindows()
  {
    closeAll();
  }

  void Browser::closeWindow(int n)
  {
    Window* window = getWindow(n);
    closeWindow(window);
  }

  void Browser::closeWindow(Window* window)
  {
    windows_.remove(window);
    delete window;
    window = NULL;
  }
  
  /////////////////////////////// PROTECTED  ///////////////////////////////////

  void Browser::generateSessionToken()
  {
    uuid_t token;
    char parsed[UUID_TOKEN_SIZE];
    uuid_generate(token);
    uuid_unparse(token, parsed);
    sessionToken_ = string(parsed, UUID_TOKEN_SIZE);
  }
}

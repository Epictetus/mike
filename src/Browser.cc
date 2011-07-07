#include <string.h>
#include <uuid/uuid.h>
#include "http/Request.h"
#include "utils/SystemInfo.h"
#include "utils/Helpers.h"
#include "Page.h"
#include "Window.h"
#include "Browser.h"

namespace mike
{
  using namespace http;
  
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
    expected_popups_.clear();
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

  void Browser::enableCookies()
  {
    cookieEnabled_ = true;
  }

  void Browser::disableCookies()
  {
    cookieEnabled_ = false;
  }

  void Browser::enableJava()
  {
    javaEnabled_ = true;
  }

  void Browser::enableJavaScript()
  {
    enableJava();
  }

  void Browser::disableJava()
  {
    javaEnabled_ = false;
  }

  void Browser::disableJavaScript()
  {
    disableJava();
  }

  Window* Browser::newWindow()
  {
    Window* window = new Window(this);
    windows_.push_back(window);
    return window;
  }
  
  // XXX: in the future it should return read only list...
  list<Window*>& Browser::getWindows()
  {
    return windows_;
  }

  Window* Browser::getWindow(int n)
  {
    if (n < windows_.size()) {
      list<Window*>::iterator it = windows_.begin();
      advance(it, n);
      return *it;
    }

    throw WindowNotExistsError();
  }

  //============================= EXPECTATIONS =================================

  void Browser::expectAlert()
  {
    PopupExpectation e;
    e.kind = kPopupAlert;
    e.flags = kSkipMessage;
    expected_popups_.push_back(e);
  }

  void Browser::expectAlert(string msg)
  {
    PopupExpectation e;
    e.kind = kPopupAlert;
    e.flags = kMatchMessage;
    e.message = msg;
    expected_popups_.push_back(e);
  }

  void Browser::expectAlerts(int n)
  {
    while (n-- > 0)
      expectAlert();
  }

  void Browser::expectConfirmation(bool choice)
  {
    PopupExpectation e;
    e.kind = kPopupConfirm;
    e.flags = kSkipMessage;
    e.choice = choice ? "yes" : "no";
    expected_popups_.push_back(e);
  }

  void Browser::expectConfirmation(string msg, bool choice)
  {
    PopupExpectation e;
    e.kind = kPopupConfirm;
    e.flags = kMatchMessage;
    e.message = msg;
    e.choice = choice ? "yes" : "no";
    expected_popups_.push_back(e);
  }

  void Browser::expectConfirmations(int n, bool choice)
  {
    while (n-- > 0)
      expectConfirmation(choice);
  }
  
  //============================= OPERATIONS ===================================

  Page* Browser::open(string url)
  {
    Window* window = newWindow();
    Page* page = Page::Open(url, cookieEnabled_, sessionToken_);
    window->setPage(page);    
    return page;
  }

  Page* Browser::getPage(string url)
  {
    open(url);
  }
  
  void Browser::closeAll()
  {
    delete_all< list<Window*> >(&windows_);
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
